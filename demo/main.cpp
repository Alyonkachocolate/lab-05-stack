#include <stack_1.hpp>
#include <utility>
class Item_1 {
 private:
  double val1;
  int val2;
  int val3;
  std::string val4;

 public:
  Item_1() : val1(0.1), val2(2), val3(3), val4("4") {}
  Item_1(double val1_, int val2_, int val3_, std::string val4_)
      : val1(val1_), val2(val2_), val3(val3_), val4(std::move(val4_)) {}

  [[maybe_unused]] void print() {
    std::cout << "Item_1\n"
              << val1 << " " << val2 << " " << val3 << " " << val4 << std::endl;
  }
};

int main() {
  std::cout << "stack" << std::endl;

  Stack<int> stack;
  stack.print();

  int x = 3;
  stack.push(x);
  stack.print();

  stack.push(5);
  stack.print();

  stack.pop();
  stack.print();

  stack.push(8);
  stack.print();

  Stack<int> stack1(std::move(stack));
  std::cout << "stack" << std::endl;
  stack.print();
  std::cout << "stack1" << std::endl;
  stack1.print();

  Stack<int> stack2 = std::move(stack1);
  std::cout << "stack" << std::endl;
  stack.print();
  std::cout << "stack1" << std::endl;
  stack1.print();
  std::cout << "stack2" << std::endl;
  stack2.print();

  std::cout << "stack3" << std::endl;
  Stack<Item_1> stack3;
  stack3.push_emplace(0.1, 20, 30, "40");
  Item_1 Item = stack3.head();
  Item.print();

  stack3.push({0.2, 40, 60, "80"});
  Item = stack3.head();
  Item.print();

  Item_1 Item_1{0.3, 60, 90, "120"};
  stack3.push(Item_1);
  Item = stack3.head();
  Item.print();
}
