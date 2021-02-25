import random
def partition_3_old(array, l, r):
    pivot_point = random.randint(l, r-1)
    array[l], array[pivot_point] = array[pivot_point], array[l]
    pivot = array[l]
    j = l

    for i in range(l+1, r):
        if array[i] <= pivot:
            j += 1
            array[j], array[i] = array[i], array[j]
    array[l], array[j] = array[j], array[l]
    k = j
    for i in range(l, j-1):
        if array[i] == pivot:
            k -= 1
            array[k], array[i] = array[i], array[k]
    return (j, k)

def partition_3(array, l, r):
    pivot_point = random.randint(l, r-1)
    pivot = array[pivot_point]
    lss, eql, grt = [], [], []
    for i in range(l, r):
        if array[i] < pivot:
            lss.append(array[i])
        elif array[i] == pivot:
            eql.append(array[i])
        else:
            grt.append(array[i])
    array[l:l+len(lss)] = lss
    array[l+len(lss):l+len(lss)+len(eql)] = eql
    array[l+len(lss)+len(eql):r] = grt

    # array[l:r] = lss + eql + grt

    return (l+len(lss), l+len(lss)+len(eql))

def quicksort_3(array, l, r):
    if r - l < 2:
        return
    pivot_point_l, pivot_point_r = partition_3(array, l, r)
    quicksort_3(array, l, pivot_point_l)
    quicksort_3(array, pivot_point_r, r)

def binary_search_1(mas, el):
    l, r = 0, len(mas)

    while l < r:
        mid = (r + l) // 2
        if el >= mas[mid]:
            l = mid + 1
        else:
            r = mid
    return l

def binary_search_2(mas, el):
    l, r = 0, len(mas)

    while l < r:
        mid = (r + l) // 2
        if el > mas[mid]:
            l = mid + 1
        else:
            r = mid
    return l

def point_and_segment():
    n, m = map(int, input().split())
    start_segment = [None] * n
    finish_segment = [None] * n
    for i in range(n):
        start_segment[i], finish_segment[i] = map(int, input().split())
    # start_segment.sort()
    # finish_segment.sort()
    quicksort_3(start_segment, 0, n)
    quicksort_3(finish_segment, 0, n)

    for point in map(int, input().split()):
        open = binary_search_1(start_segment, point)
        close = binary_search_2(finish_segment, point)
        print(open - close, end=' ')

point_and_segment()
mas = [5, 6, 5, 3, 1, 9, 1, 6, 5, 39, 30, 2, 2]
print(mas)
quicksort_3(mas, 0, len(mas))
print(mas)
# partition_3(mas, 0, len(mas))
# print(mas)