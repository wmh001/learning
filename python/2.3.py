# 字符串用''或""标记
# 修改字符串大小写
name = "add lovelace"
# 单词首字母大写
print(name.title())
# 全部大写
name = "Add Lovelace"
print(name.upper())
# 全部小写
print(name.lower())
# 拼接字符串
first_name = "ada"
last_name = "lovelace"
full_name = first_name + " " + last_name
print(full_name)
print("Hello, " + full_name.title() + "!")
# 制表符
print("\tPython")
# 换行符
print("Language:\n\tPython\n\tC\n\tJavaScript")
# 删除末尾空白，不改变原字符串
favorite_language = 'python '
print("\'" + favorite_language + "\'")
print("\'" + favorite_language.rstrip() + "\'")
print("\'" + favorite_language + "\'")
favorite_language = favorite_language.rstrip()
print("\'" + favorite_language + "\'")
# 删除开头空白
favorite_language = ' python '
print("\'" + favorite_language.rstrip() + "\'")
print("\'" + favorite_language.lstrip() + "\'")
# 删除两端空白
print("\'" + favorite_language.strip() + "\'")
