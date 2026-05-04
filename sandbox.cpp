extern "C"
{
    __attribute__((visibility("default")))
    int Add(int a, int b)
    {
        return a+b;
    }

    __attribute__((visibility("default")))
    int Multiply(int a, int b)
    {
        return a*b;
    }
}
