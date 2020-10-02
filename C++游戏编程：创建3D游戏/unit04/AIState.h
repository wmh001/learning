#pragma once
class AIState
{
public:
	AIState(class AIComponent* owner)
		:mOwner(owner)
	{ }
	//  状态特殊行为
	//  更新
	virtual void Update(float deltaTime) = 0;
	//  加入
	virtual void OnEnter() = 0;
	//  退出
	virtual void OnExit() = 0;
	//  访问名字
	virtual const char* GetName() const = 0;
protected:
	//  拥有者
	class AIComponent* mOwner;
};
//  巡逻
class AIPatrol : public AIState
{
public:
	AIPatrol(class AIComponent* owner)
		:AIState(owner)
	{ }
	//  此状态的特殊行为
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;
	const char* GetName() const override
	{
		return "Patrol";
	}
};

//  死亡
class AIDeath : public AIState
{
public:
	AIDeath(class AIComponent* owner)
		:AIState(owner)
	{ }
	//  此状态的特殊行为
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;
	const char* GetName() const override
	{
		return "Death";
	}
};

//  攻击
class AIAttack : public AIState
{
public:
	AIAttack(class AIComponent* owner)
		:AIState(owner)
	{ }
	//  此状态的特殊行为
	void Update(float deltaTime) override;
	void OnEnter() override;
	void OnExit() override;
	const char* GetName() const override
	{
		return "Attack";
	}
};