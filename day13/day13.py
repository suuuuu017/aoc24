import re

def find3(A, B, target):
    det = A[0] * B[1] - A[1] * B[0]
    detA = target[0] * B[1] - target[1] * B[0]
    detB = A[0] * target[1] - A[1] * target[0]

    print(A[0], A[1], B[0], B[1], target[0], target[1])
    print(A[0] * B[1], detA, detB)

    if detA == 0 or detA % det != 0 or detB % det != 0:
        return 0
    elif detA // det < 0 or detB // det < 0:
        return 0
    else:
        return detA // det * 3 + detB // det * 1


def main():
    filename = input("Enter the file name: ")

    with open(filename, 'r') as file:
        res = 0

        while True:
            line = file.readline()
            if not line:
                break

            block = ''
            nums = []

            # Read the entire block
            while line.strip():
                block += line
                line = file.readline()
                if not line:
                    break

            # Extract all the numbers from the block using regex
            nums = [int(num) for num in re.findall(r'-?\d+', block)]

            # Assuming that the input contains 6 numbers as in the original code
            A = (nums[0], nums[1])
            B = (nums[2], nums[3])
            target = (nums[4] + 10000000000000, nums[5] + 10000000000000)

            tmp = find3(A, B, target)
            print(tmp)
            res += tmp

        print(res)


if __name__ == "__main__":
    main()
