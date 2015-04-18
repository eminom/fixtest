
if __name__ == "__main__":
    from FixTest import Fixed16
    a = Fixed16(20)
    a = Fixed16(20) + 20.0
    a = 20.0 / Fixed16(30)
    a = Fixed16(100) * Fixed16(20.3)

    print("")
    print("Test inplace operator:")
    a/=20.0
    a/=a
    try:
        a = Fixed16(0)
        print("a = ", a)
        x = 30.0
        x /= a
        print(x)
    except:
        print("Error happed")
        raise

