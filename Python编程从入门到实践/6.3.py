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
