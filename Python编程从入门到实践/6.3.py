# 遍历字典

# 遍历所有键-值对
user_0 = {
    'username': 'efermi',
    'first': 'enrico',
    'last': 'fermi',
}
# 字典.items()返回键-值对列表
for key, value in user_0.items():
    print("\nKey: " + key)
    print("Value" + value)

favorite_languages = {
    'jen': 'python',
    'sarah': 'c',
    'edward': 'rudy',
    'phil': 'python',
}

for name, language in favorite_languages.items():
    print(
        name.title() + "'s favorite language is " +
        language.title() +
        ".")

# 遍历字典中的所有键
# 字典.keys()返回键列表
for name in favorite_languages.keys():
    print(name.title())

# 缺省时，默认遍历键
for name in favorite_languages:
    print(name.title())

# 遍历时，对于选定键施加特殊处理
friends = ['phil', 'sarah']
for name in favorite_languages.keys():
    print(name.title())

    if name in friends:
        print("  Hi " + name.title() +
              ", I see your favorite language is "
              + favorite_languages[name].title())

if 'erin' not in favorite_languages.keys():
    print("Erin, please take our poll")

# 按键顺序遍历
# sorted(列表)返回排序后的列表
for name in sorted(favorite_languages.keys()):
    print(name.title() + ", thank you for taking the poll.")

# 遍历值
print("The follow languages have been mentioned:")
for language in favorite_languages.values():
    print(language.title())

# 遍历但除去重复值，顺序不定
for language in set(favorite_languages.values()):
    print(language.title())
