#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}

    // Silly to use a vector to initialize a list, but easiest way to get values to this custom list class :)
    static ListNode* Create(std::vector<int> digits)
    {
        ListNode* head = nullptr;

        auto itr = digits.begin();
        while (itr != digits.end())
        {
            ListNode* newNode = new ListNode(*itr);
            newNode->next = head;
            head = newNode;
            itr++;
        }

        return head;
    }

    static void Delete(ListNode* head)
    {
        while (head)
        {
            ListNode* cur = head;
            head = head->next;
            delete cur;
        }
    }

    static bool Compare(ListNode* head, std::vector<int> digits)
    {
        auto itr = digits.rbegin();
        while (itr != digits.rend() && head)
        {
            if (*itr != head->val)
            {
                return false;
            }

            itr++;
            head = head->next;
        }

        return true;
    }
};

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode* head = nullptr;
        ListNode* cur = nullptr;
        bool carry = false;

        // Keep adding digits to the final sum while either list still contains a digit or we have a carry digit
        while (l1 || l2 || carry)
        {
            int value1 = l1 ? l1->val : 0;
            int value2 = l2 ? l2->val : 0;
            int sum = value1 + value2 + (carry ? 1 : 0);
            carry = sum >= 10;

            ListNode* newNode = new ListNode(sum % 10);
            if (!head)
            {
                head = newNode;
                cur = newNode;
            }
            else
            {
                cur->next = newNode;
                cur = newNode;
            }

            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
        }

        return head;
    }
};

TEST_CASE("AddTwoNumbers", "[tests]")
{
    Solution solution;
    ListNode* l1 = nullptr;
    ListNode* l2 = nullptr;
    ListNode* solutionList = nullptr;

    SECTION("LeetCode Sample Input")
    {
        l1 = ListNode::Create({3, 4, 2});
        l2 = ListNode::Create({4, 6, 5});
        solutionList = solution.addTwoNumbers(l1, l2);
        REQUIRE(ListNode::Compare(solutionList, {8, 0, 7}));
    }

    SECTION("Empty")
    {
        solutionList = solution.addTwoNumbers(nullptr, nullptr);
        REQUIRE(solutionList == nullptr);
    }

    SECTION("Single List")
    {
        l1 = ListNode::Create({3, 4, 2});
        solutionList = solution.addTwoNumbers(l1, nullptr);
        REQUIRE(ListNode::Compare(solutionList, {3, 4, 2}));
    }

    SECTION("Different Lengths")
    {
        l1 = ListNode::Create({1, 2, 3});
        l2 = ListNode::Create({4, 5, 6, 7});
        solutionList = solution.addTwoNumbers(l1, l2);
        REQUIRE(ListNode::Compare(solutionList, {4, 6, 9, 0}));
    }

    SECTION("Extra Carry")
    {
        l1 = ListNode::Create({6, 1, 2, 3});
        l2 = ListNode::Create({4, 5, 6, 7});
        solutionList = solution.addTwoNumbers(l1, l2);
        REQUIRE(ListNode::Compare(solutionList, {1, 0, 6, 9, 0}));
    }

    SECTION("Carries")
    {
        l1 = ListNode::Create({9, 9, 9});
        l2 = ListNode::Create({9, 9, 9});
        solutionList = solution.addTwoNumbers(l1, l2);
        REQUIRE(ListNode::Compare(solutionList, {1, 9, 9, 8}));
    }

    ListNode::Delete(l1);
    ListNode::Delete(l2);
    ListNode::Delete(solutionList);
}