# ft_containers

## convention

### clion

- `typedef` 한 type 의 타입명 앞에는 `_` 쓰면 안됌.

- private class `_className`
- private / protected variables `_name`
- 메모리 관련 함수 / 변수 `_m_name`
- 기본적으로 다 `snake_case`
- google style guide link : http://jongwook.kim/google-styleguide/trunk/cppguide.xml

## iterator_traits

### container_iterator 가 iterator_traits 를 상속 받는 이유

`iterator_traits` 클래스를 상속받지 않아도 되지만 상속을 받아 구현하는 것이 C++ 표준 라이브러리의 알고리즘 및 라이브러리에서 예상하는 표준 인터페이스를 제공하므로 더 좋은 방법이다.
`iterator_traits` 클래스는 반복자 유형 특성을 추출하는[iterator_traits.hpp](stl%2Finclude%2Fiterator_traits.hpp)데 사용할 수 있지만 사용자 정의 반복자의
기본 클래스로 사용하도록 설계되지는 않았다. `iterator_traits` 클래스를 상속받아
`input_iterator`, `output_iterator`, `random_access_iterator` 등의 반복자 유형을 지정하여 구현할 수 있다. 이를 통해 표준 라이브러리와의 호환성 및 상호 운용성이
향상된다.

### iterator_traits 종류

- Input iterator_traits : 전진만 가능, 한번에 하나만 읽기 가능
- Output iterator_traits : 전진만 가능, 한번에 하나만 쓰기 가능
- Forward iterator_traits : 전진만 가능, 한번에 여러개 읽고 쓰기 가능
- Bidirectional iterator_traits : 전/후진 모두 가능, 한번에 여러개 읽고 쓰기 가능
- Random access iterator_traits : 반복자를 임의의 위치만큼 전/후진 가능

| Iterator 기능          | Input | Output | Forward | Bidirectional | Random access |
|----------------------|-------|--------|---------|---------------|---------------|
| 접근(->)               | ○     | X      | ○       | ○             | ○             |
| 읽기(*)                | ○     | X      | ○       | ○             | ○             |
| 쓰기(*)                | X     | ○      | ○       | ○             | ○             |
| 증가 연산자(++)           | ○     | ○      | ○       | ○             | ○             |
| 감소 연산자(--)           | X     | X      | X       | ○             | ○             |
| 첨자 연산자([])           | X     | X      | X       | X             | ○             |
| 산술 연산자(+, -)         | X     | X      | X       | X             | ○             |
| 산술 대입 연산자(+=, -=)    | X     | X      | X       | X             | ○             |
| 관계 연산자(<, <=, >, >=) | X     | X      | X       | X             | ○             |

## allocator

- `<memory>` 헤더에 존재함
- 유연한 메모리 관리를 해주는 클래스
- 주로 라이브러리를 작성할 때, 특히 표준 라이브러리의 컨테이너를 구현할 때 많이 사용하는 클래스
- 할당자는 메모리 관리를 좀 더 세밀하게 컨트롤해야할 수 있는 `fine-grained` 방식
- 개발자가 원하는 방식으로 메모리 할당 방식을 정할 수 있음

### `new` 연산자가 아닌 `allocator`를 사용해야하는 이유

- `new` 연산자로 메모리 동적 할당을 하게 되면 **메모리 할당 + 요소 초기화** 과정이 동시에 일어남
- `allocator` 로 메모리를 관리하게 되면 **메모리 할당** 과 **요소 초기화** 를 분리해서 관리할 수 있음

### `allocator` 주요 함수

```c++
template <class T>
class allocator
{
public:
   T* allocate(size_t);
   void deallocate(T*, size_t);
   void construct(T*, const T&);
   void destory(T*);
   
   ....
};

template <class In, class For>
For uninitialized_copy(In, In, For);

template <class For, class T>
void uninitialized_fill(For, For, const T&);
```

- `allocate` : 초기화 되지 않은 메모리 공간을 할당 후, 그 시작 주소를 반환하는 함수
- `deallocate` : 메모리 공간을 해제하는 함수
- `construct` : 초기화 되지 않은 공간에 요소를 저장하는 함수
- `destroy` : 요소를 소멸시키는 함수
- `uninitialize_copy`
    - STL 의 `std::copy` 와 비슷한 함수. [first, last) 범위의 요소들을 순방향 반복자가 가리키는 위치에 순서대로 복사한다. 그리고 복사가 완료된 위치의
      다음 요소를 가리키는 포인터를 반환한다. -> 중간에 요소 삽입하다가 에러나면 이전의 상태로 바꿔줌
    - 복사 한 후 맨 마지막 iterator_traits 를 반환한다. (즉, end() 의 iterator_traits 를 반환함)
- `uninitialized_fill`
    - 3번째 인자의 value 로 [first, last) 까지 채운다.
- `uninitialized_fill_n`
    - 메모리 공간에 n 만큼 val 값을 채워줌

# RAII

- `RAII` 는 **생성자에서 자원을 획득하고 해당 소멸자에서 해제하는 것을 말한다.**
- 메모리 누수, 교착 상태, 스레드 종료 등의 예상치 못한 문제들은 리소스 범위를 벗어나면 문제가 발생하게 된다.
- 리소스는 힙 메모리, 파일, 소켓, 뮤텍스 등을 가리킨다.
- 생성자에서 리소스를 획득하고 해당 소멸자에서 해제하면 리소스 수명이 개체 수명에 바인딩되므로 더 이상 리소스를 획득할 때마다 명시적으로 해제해야한다는 것을 기억할 필요가 없게 된다.

# template 특수화

`template 특수화` 란 특정한 템플릿 매개변수를 받을 때에 대한 코드를 커스터 마이즈 한 것이다.

```c++
template <class T>
Equals (T lhs, T rhs) {
  return lhs == rhs;
}

// template 특수화
template <>
Equals (float lhs, float rhs) {
  return false; // float 이 왔을때는 언제나 false 로 반환하게 커스터마이즈 하고 싶을 때 
}
```

## SIFNAE

- **Substitution Failure Is Not An Error 의 약자**
- **치환 실패는 오류가 아니다** 라는 뜻으로 **템플릿 치환 후에 만들어진 식이 문법적으로 맞지 않는다면, 컴파일 오류를 발생 시키는 대신 단수히 함수의 오버로딩 후보군에서 제외만 시키게 된다.**
- `SIFNAE` 를 활용하면 내가 원하지 않는 타입들에 대해서 오버로딩 후보군에서 제외할 수 있다.
- `SIFNAE` 를 적극적으로 활용할 수 있도록 하는 메타 템플릿 함수의 대표적인 예시로 `enable_if` 가 있다.
- 치환을 시도 할 때, `SIFNAE` 에 의해 모든 경우에 수가 오버로딩 후보군에서 제외 되었을 때는 `no matching function for call` 컴파일 오류가 뜨게 된다.

# type_traits

type_traits 헤더 안에는 템플릿 메타 함수들이 구현되어 있다. 템플릿 메타함수란 사실 함수는 아니지만 마치 함수 처럼 동작하는 템플릿 클래스들을 이야기 한다. 템플릿 함수는 보값에 대한 연산을 수행하는 것이
아니라 타입에 대한 연산을 수행한다.

### enable_if

### is_integral

- `is_integral` 클래스는 `integral_constant` 를 상속 받고 있

### equal

### lexicographical_compare

### pair

### make_pair

### etc

- `is_same`
    - T 와 U 의 타입이 같은지 알려주는 템플릿 함수
    - `integral constant` 를 상속받고 있음
- `is_iterator`
    - `iterator` 인지 확인해주는 템플릿 함수
  ```c++
    template<typename T>

    struct is_iterator {
    private:
      // yes, no 를 판별할 두 가지 다른 타입 유형을 설정
      typedef char yes;
      typedef long no;
      
      // U * 을 통해 타입을 추론하고, iterator_category 가 있는지 확인 
      template<typename U>
      static yes test(U *, typename U::iterator_category * = 0);
      
      static no test(...);
    public:
      enum { value = sizeof(test(static_cast<T *>(0))) == sizeof(yes) };
    };
    
    ```

# vector

`vector` 는 크기가 변경될 수 있는 배열을 나타내는 `sequence container` 이다. 배열과 마찬가지로 벡터는 요소에 대해 연속적인 저장 위치를 사용한다.
그러나 배열과 다르게 메모리 공간이 컨테이너에 의해 자동으로 처리되므로 크기가 동적으로 변경될 수 있다.

**벡터 특징**

- 선형적 자료구조. 개별 요소들을 순서에 따른 위치로 액세스 가능하다.
- 동적 배열. 포인터를 통해서도 모든 요소에 직접 액세스 가능하다.
- 할당자 인식(allocator aware). allocator 개체를 사용하여 동적으로 공간을 할당한다.

1. `vector_iterator` 구현
2. `vector_base` 구현
    - vector 클래스의 힙 메모리 리소스 관리 담당
    - RAII 패턴을 적용해서 벡터의 리소스를 할당하고 소멸자를 통해 전체 리소스를 해제해주는 클래스

# Reference

https://woo-dev.tistory.com/51
https://medium.com/swlh/what-is-raii-e016d00269f9
https://modoocode.com/295