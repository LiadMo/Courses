def isPalindrome(string):
    if not string:
        return False
    return string == string[::-1]


def get_palindrom_dict(str):
    hist = {}

    for K in range(1, len(str) + 1):
        res = [str[i: j] for i in range(len(str)) for j in range(i + 1, len(str) + 1) if
               len(str[i:j]) == K and isPalindrome(str[i:j])]
        if res:
            hist[K] = res
    return hist


def check_match(str):
    hist = {}

    if len(str) % 2 != 0:
        return False

    first_word = str[::2]
    second_word = str[1::2]

    for first, second in zip(first_word, second_word):
        if first not in hist or hist[first] == second:
            hist[first] = second
        else:
            return False
    return True
