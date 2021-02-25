def search_i_eq_m_i(mas):
    l, r = 0, len(mas)-1

    while l <= r:
        mid = (r + l) // 2
        if mas[mid] == mid+1:
            return True
        if mas[mid] < mid+1:
            l = mid + 1
        else:
            r = mid - 1
    return False

def binary_search(mas, el):
    l, r = 0, len(mas)-1

    while l <= r:
        mid = (r + l) // 2
        if mas[mid] == el:
            return mid+1
        if mas[mid] < el:
            l = mid + 1
        else:
            r = mid - 1
    return -1

def main():
    # _, *mas = map(int, input().split())
    # _, *mas_inp = map(int, input().split())
    # for el in mas_inp:
    #     print(binary_search(mas, el), end=' ')
    mas = [1, 2, 6, 7, 8, 9]
    mas1 = [0, 1, 2, 3, 4, 6]
    mas2 = [2, 3, 4, 5, 6, 7, 8, 9]
    mm = [mas, mas1, mas2]
    for m in mm:
        print(search_i_eq_m_i(m))

if __name__ == "__main__":
    main()