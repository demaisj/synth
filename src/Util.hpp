namespace Util {

  template <class C>
  C &singleton()
  {
    static C instance;

    return instance;
  }

  template <typename T>
  T abs(T x)
  {
    return x < T(0) ? -x : x;
  }

}