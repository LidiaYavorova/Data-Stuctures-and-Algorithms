# Data-Stuctures-and-Algorithms
## Expression evaluation

В това задание трябва да реализирате функционалността нужна за програма, която обработва изрази.

Като аргументи от командния ред програмата ще получава инфиксен израз и файл, който описва операторите използвани в израза. Тя трябва да пресметне израза и да изведе получения резултат на екрана.

## Bar simulation

В това задание трябва да реализирате функционалността нужна за програма, която симулира управление на студентски бар.

Програмата ще комуникира с потребителя през стандартния вход и изход.

Структурата от данни, която трябва да използвате в задачата е свързан списък (Linked List).

 ## Binary Search Tree (BST)

Множество от цели числа без повторение на елементите ще представяме чрез описания по-долу клас.

```cpp
class IntegerSet {
private:
  // Добавете подходящи член-данни

public:
  IntegerSet();
  IntegerSet(const IntegerSet&);
  IntegerSet& operator=(const IntegerSet&);
  ~IntegerSet();

public:
  // Връща броя на елементите в множеството
  size_t size() const;

  /// Проверява дали елемент се съдържа в множество
  bool countains(int) const;

  /// Проверява дали две множества се състоят от едни и същи елементи
  bool equals(const IntegerSet&) const;

  /// Проверява дали текущият обект е подмножество на друг
  bool subsetOf(const IntegerSet&) const;

  /// Връща обединението на две множества
  IntegerSet getUnion(const IntegerSet&) const;
  
  /// Връща сечението на две множества
  IntegerSet getIntersection(const IntegerSet&) const;

  /// Десериализира съдържанието на едно множество.
  /// Новата информация напълно заменя старата.
  void deserialize(std::istream&);

  /// Сериализира съдържанието на едно множество
  void serialize(std::ostream&) const;
};

inline std::istream& operator>>(std::istream& in, IntegerSet& set)
{
  set.deserialize(in);
  return in;
}

inline std::ostream& operator<<(std::ostream& out, const IntegerSet& set)
{
  set.serialize(out);
  return out;
}
```

Реализирайте всички операции на класа.
