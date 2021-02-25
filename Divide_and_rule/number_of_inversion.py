def merge(mas1, cnt1, mas2, cnt2):
    len_mas1 = len(mas1)
    len_mas2 = len(mas2)
    i, j = 0, 0
    result_mas = []
    cnt = cnt1 + cnt2
    while i < len_mas1 and j < len_mas2:
        if(mas1[i] <= mas2[j]):
            result_mas.append(mas1[i])
            i += 1
        else:
            result_mas.append(mas2[j])
            j += 1
            cnt += len_mas1-i
    if i == len_mas1:
        result_mas.extend(mas2[j:])
    else:
        result_mas.extend(mas1[i:])
    return (result_mas, cnt)

def merge_sort(mas, l, r):
    if r - l < 2:
        return ([mas[l]], 0)
    mid = l + (r - l)//2
    return merge(*merge_sort(mas, l, mid), *merge_sort(mas, mid, r))

def main():
    # input()
    # mas = [int(i) for i in input().split()]
    mas = [4,5,5,4,3]
    cnt = 0
    for i in range(len(mas)):
        for j in range(i+1, len(mas)):
            if mas[i] > mas[j]:
                cnt += 1

    print(cnt)
    print(merge_sort(mas, 0, len(mas))[1])

if __name__ == "__main__":
    main()