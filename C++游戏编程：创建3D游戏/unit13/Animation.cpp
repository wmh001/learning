#include "Animation.h"
#include "Skeleton.h"
#include <fstream>
#include <sstream>
#include <document.h>
#include <SDL_log.h>


bool Animation::Load(const std::string& fileName)
{
	//  打开文件
	std::ifstream file(fileName);
	//  失败处理
	if (!file.is_open())
	{
		SDL_Log("File not found: Animation %s", fileName.c_str());
		return false;
	}
	//  文件内容转换为字符串
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		SDL_Log("Animation %s is not valid json", fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the metadata
	if (ver != 1)
	{
		SDL_Log("Animation %s unknown format", fileName.c_str());
		return false;
	}

	const rapidjson::Value& sequence = doc["sequence"];
	if (!sequence.IsObject())
	{
		SDL_Log("Animation %s doesn't have a sequence.", fileName.c_str());
		return false;
	}

	const rapidjson::Value& frames = sequence["frames"];
	const rapidjson::Value& length = sequence["length"];
	const rapidjson::Value& bonecount = sequence["bonecount"];

	if (!frames.IsUint() || !length.IsDouble() || !bonecount.IsUint())
	{
		SDL_Log("Sequence %s has invalid frames, length, or bone count.", fileName.c_str());
		return false;
	}

	mNumFrames = frames.GetUint();
	mDuration = length.GetDouble();
	mNumBones = bonecount.GetUint();
	mFrameDuration = mDuration / (mNumFrames - 1);

	mTracks.resize(mNumBones);

	const rapidjson::Value& tracks = sequence["tracks"];

	if (!tracks.IsArray())
	{
		SDL_Log("Sequence %s missing a tracks array.", fileName.c_str());
		return false;
	}

	for (rapidjson::SizeType i = 0; i < tracks.Size(); i++)
	{
		if (!tracks[i].IsObject())
		{
			SDL_Log("Animation %s: Track element %d is invalid.", fileName.c_str(), i);
			return false;
		}

		size_t boneIndex = tracks[i]["bone"].GetUint();

		const rapidjson::Value& transforms = tracks[i]["transforms"];
		if (!transforms.IsArray())
		{
			SDL_Log("Animation %s: Track element %d is missing transforms.", fileName.c_str(), i);
			return false;
		}

		BoneTransform temp;

		if (transforms.Size() < mNumFrames)
		{
			SDL_Log("Animation %s: Track element %d has fewer frames than expected.", fileName.c_str(), i);
			return false;
		}

		for (rapidjson::SizeType j = 0; j < transforms.Size(); j++)
		{
			const rapidjson::Value& rot = transforms[j]["rot"];
			const rapidjson::Value& trans = transforms[j]["trans"];

			if (!rot.IsArray() || !trans.IsArray())
			{
				SDL_Log("Skeleton %s: Bone %d is invalid.", fileName.c_str(), i);
				return false;
			}
			//  获取属性
			//  四元数
			temp.mRotation.x = rot[0].GetDouble();
			temp.mRotation.y = rot[1].GetDouble();
			temp.mRotation.z = rot[2].GetDouble();
			temp.mRotation.w = rot[3].GetDouble();
			//  位置
			temp.mTranslation.x = trans[0].GetDouble();
			temp.mTranslation.y = trans[1].GetDouble();
			temp.mTranslation.z = trans[2].GetDouble();
			//  进入映射
			mTracks[boneIndex].emplace_back(temp);
		}
	}
	return true;
}

void Animation::GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const Skeleton* inSkeleton, float inTime) const
{
	//  调整轨道数为骨骼数
	if (outPoses.size() != mNumBones)
	{
		outPoses.resize(mNumBones);
	}
	//  计算帧数
	size_t frame = static_cast<size_t>(inTime / mFrameDuration);
	//  计算下一帧
	size_t nextFrame = frame + 1;
	//  计算帧和下一帧之间的分数
	float pct = inTime / mFrameDuration - frame;
	//  设置更骨骼姿势
	//  是否有轨道
	if (mTracks[0].size() > 0)
	{
		//  插值
		BoneTransform interp = BoneTransform::Interpolate(mTracks[0][frame], mTracks[0][nextFrame], pct);
		//  计算位姿矩阵
		outPoses[0] = interp.ToMatrix();
	}
	else
	{
		//  初始化为单位矩阵
		outPoses[0] = Matrix4::Identity;
	}
	//  获取骨骼容器
	const std::vector<Skeleton::Bone>& bones = inSkeleton->GetBones();
	//  设置其余骨骼的姿势
	for (size_t bone = 1; bone < mNumBones; bone++)
	{
		//  获取局部姿势矩阵
		Matrix4 localMat;
		//  是否有轨道
		if (mTracks[bone].size() > 0)
		{
			//  插值
			BoneTransform interp = BoneTransform::Interpolate(mTracks[bone][frame], mTracks[bone][nextFrame], pct);
			//  转换为矩阵
			localMat = interp.ToMatrix();
		}
		//  计算全局姿势矩阵
		outPoses[bone] = localMat * outPoses[bones[bone].mParent];
	}
}
