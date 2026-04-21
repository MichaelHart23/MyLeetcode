

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

/**
 * Floyd判圈法
 * 设圈的路径长为y（圈包含y个节点），圈之前的路径长为x（圈之前有x个节点）
 * 步长为2和步长为1的快慢指针，当二者相遇时
 * slow走过 x + m 路程 fast走过 x + m + ky 路程
 * 同时 x + m + ky = 2 *（ x + m ）
 * 所以此时 slow 走过了 x + m = ky 的路程，也就是 k 个环长
 *
 * 要走到环的入口需要走 x + ky 的路程，而此时 slow 只需再走 x 的距离就能到环的入口
 * 但不知道 x 啊，所以此时再令一个指针从头出发，走 x 的路程，该指针和 slow 相遇的地方就是
 * 环的入口
 */
class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode *fast = head, *slow = head;
        while (true) {
            if (!fast || !fast->next) return nullptr;
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) break;
        }
        while (head != slow) {
            head = head->next;
            slow = slow->next;
        }
        return slow;
    }
};