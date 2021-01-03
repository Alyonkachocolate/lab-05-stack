// Copyright [2020] <Alyona Dorodnyaya>

#include <gtest/gtest.h>

#include <stack_1.hpp>

class Item {
 private:
  double val1;
  int val2;
  std::string val3;

 public:
  Item() : val1(0), val2(0) {}
  Item(double val1_, int val2_, std::string val3_)
      : val1(val1_), val2(val2_), val3(std::move(val3_)) {}

  bool operator==(const Item& item) const {
    return (val1 == item.val1 && val2 == item.val2 && val3 == item.val3);
  }
};

TEST(Constructor, Default_constructor) {
  Stack<int> stack;
  EXPECT_TRUE(stack.empty());
}

TEST(Constructor, Move_constructor) {
  Stack<int> stack;
  stack.push(10);
  Stack<int> stack1(std::move(stack));
  EXPECT_TRUE(stack.empty());
  EXPECT_EQ(stack1.head(), 10);
  Stack<int> stack2(std::move(stack1));
  EXPECT_TRUE(stack1.empty());
  EXPECT_EQ(stack2.head(), 10);
}

TEST(Constructor, Move_operator) {
  Stack<int> stack;
  stack.push(20);
  Stack<int> stack1 = std::move(stack);
  EXPECT_TRUE(stack.empty());
  EXPECT_EQ(stack1.head(), 20);
}

TEST(Push, Push_l_value) {
  Stack<std::string> stack;
  std::string str = "Example";
  // void Stack::push(const T &value)
  stack.push(str);
  EXPECT_EQ(stack.head(), "Example");
}

TEST(Push, Push_r_value) {
  Stack<std::string> stack;
  // void Stack::push(T &&value)
  stack.push("Example");
  EXPECT_EQ(stack.head(), "Example");
}

TEST(Push, Push_emplace) {
  Stack<Item> stack;
  stack.push_emplace(0.1, 2, "3");
  EXPECT_EQ(stack.head(), Item(0.1, 2, "3"));
}

TEST(Size, Size) {
  Stack<int> stack;
  EXPECT_EQ(stack.size(), 0);
  stack.push(100);
  EXPECT_EQ(stack.size(), 1);
}

TEST(Empty, Empty) {
  Stack<int> stack;
  EXPECT_TRUE(stack.empty());
  stack.push(10);
  EXPECT_FALSE(stack.empty());
}

TEST(Head, Head) {
  Stack<Item> stack;

  EXPECT_THROW(stack.head(), std::out_of_range);

  // void Stack::push_emplace(Args &&... value)
  stack.push_emplace(0.1, 2, "3");
  EXPECT_EQ(stack.head(), Item(0.1, 2, "3"));

  // void Stack::push(T &&value)
  stack.push({0.2, 4, "6"});
  EXPECT_EQ(stack.head(), Item(0.2, 4, "6"));

  // void Stack::push(const T &value)
  Item item{0.3, 6, "9"};
  stack.push(item);
  EXPECT_EQ(stack.head(), Item(0.3, 6, "9"));
}

TEST(Pop, Pop) {
  Stack<double> stack;
  stack.push(0.1);
  EXPECT_EQ(stack.head(), 0.1);
  stack.push(0.2);
  EXPECT_EQ(stack.head(), 0.2);

  stack.pop();
  EXPECT_EQ(stack.head(), 0.1);

  stack.pop();
  EXPECT_TRUE(stack.empty());

  EXPECT_THROW(stack.pop(), std::out_of_range);
}
