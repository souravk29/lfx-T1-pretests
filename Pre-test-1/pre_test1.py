def collectNums(lists, threshold):
    result = 0
    for x in lists:
        if x > threshold:
            threshold = x
            result += 2 * x
    return result
print(collectNums([1, 3, 4, 2, 4, 7], 3))   