# coding: windows-1251
import statistics
from typing import Callable, Dict, Any, List
import matplotlib.pyplot as plt


# ==============================
# ��������� ��������� ����� (LCG)
# ==============================
class LCG:
    def __init__(self, seed: int = 123456):
        self.m = 2**31 - 1
        self.a = 1103515245
        self.c = 12345
        self.state = seed

    def rand(self) -> float:
        """����� � [0,1)."""
        self.state = (self.a * self.state + self.c) % self.m
        return self.state / self.m

    def randint(self, low: int, high: int) -> int:
        """��������� ����� �� ��������� [low, high]."""
        return low + int(self.rand() * (high - low + 1))


rng = LCG(seed=42)  # ������ ���������


# ==============================
# 1. ���� � ��������
# ==============================
def simulate_tokens(x: int, y: int, z: int) -> int:
    players = [x, y, z]
    rounds = 0
    while all(p > 0 for p in players):
        rounds += 1
        for i in range(3):
            players[i] -= 1
        winner = rng.randint(0, 2)
        players[winner] += 3
    return rounds


# ==============================
# 2. ���� � ��������
# ==============================
def simulate_dice(to_score: int = 20) -> Dict[str, Any]:
    scores = [0, 0]
    turns = 0
    while max(scores) < to_score:
        for player in range(2):
            roll = rng.randint(1, 6)
            scores[player] += roll
            turns += 1
            if scores[player] >= to_score:
                return {"winner": player + 1, "turns": turns}


# ==============================
# 3. ���������� ��������
# ==============================
def simulate_blackjack(strategy_threshold: int = 17) -> Dict[str, Any]:
    def draw_card():
        return rng.randint(1, 11)

    # �����
    player_sum = 0
    while player_sum < strategy_threshold:
        player_sum += draw_card()
        if player_sum > 21:
            return {"winner": "dealer", "player_sum": player_sum, "dealer_sum": None}

    # �����
    dealer_sum = 0
    while dealer_sum < 17:
        dealer_sum += draw_card()
        if dealer_sum > 21:
            return {"winner": "player", "player_sum": player_sum, "dealer_sum": dealer_sum}

    if player_sum > dealer_sum:
        return {"winner": "player", "player_sum": player_sum, "dealer_sum": dealer_sum}
    elif dealer_sum > player_sum:
        return {"winner": "dealer", "player_sum": player_sum, "dealer_sum": dealer_sum}
    else:
        return {"winner": "draw", "player_sum": player_sum, "dealer_sum": dealer_sum}


# ==============================
# Monte Carlo Runner
# ==============================
def monte_carlo(sim_func: Callable, n_simulations: int, *args, **kwargs) -> List[Any]:
    results = [sim_func(*args, **kwargs) for _ in range(n_simulations)]
    return results


# ==============================
# ������ � ������������
# ==============================
if __name__ == "__main__":

    # ---------- ������ ----------
    print("\n=== ������ ===")
    start_configs = [(5, 5, 5), (10, 1, 1), (8, 7, 2)]
    avg_rounds = []
    for config in start_configs:
        results = monte_carlo(simulate_tokens, 3000, *config)
        mean_r = statistics.mean(results)
        avg_rounds.append(mean_r)
        print(f"��������� {config}: ������� ����� ������� = {mean_r:.2f}")

    plt.bar([str(c) for c in start_configs], avg_rounds)
    plt.title("������: ������� ����� ������� ��� ������ ��������� ��������")
    plt.ylabel("������� ����� �������")
    plt.show()

    # ---------- ������ ----------
    print("\n=== ������ ===")
    dice_results = monte_carlo(simulate_dice, 5000, to_score=20)
    avg_turns = statistics.mean([r["turns"] for r in dice_results])
    p1_wins = sum(1 for r in dice_results if r["winner"] == 1) / len(dice_results)
    p2_wins = 1 - p1_wins
    print(f"������� ����� �����: {avg_turns:.2f}")
    print(f"����������� ������: �����1={p1_wins:.3f}, �����2={p2_wins:.3f}")

    plt.hist([r["turns"] for r in dice_results], bins=30, edgecolor="black")
    plt.title("������: ������������� ����� �����")
    plt.xlabel("����")
    plt.ylabel("�������")
    plt.show()

    plt.bar(["����� 1", "����� 2"], [p1_wins, p2_wins])
    plt.title("������: ����������� ������")
    plt.ylabel("�����������")
    plt.show()

    # ---------- �������� ----------
    print("\n=== �������� ===")
    strategies = range(15, 21)  # ������ 15�20
    player_win_rates = []
    dealer_win_rates = []
    draw_rates = []

    for threshold in strategies:
        results = monte_carlo(simulate_blackjack, 5000, strategy_threshold=threshold)
        p_wins = sum(1 for r in results if r["winner"] == "player") / len(results)
        d_wins = sum(1 for r in results if r["winner"] == "dealer") / len(results)
        draws = sum(1 for r in results if r["winner"] == "draw") / len(results)
        player_win_rates.append(p_wins)
        dealer_win_rates.append(d_wins)
        draw_rates.append(draws)
        print(f"����� {threshold}: �����={p_wins:.3f}, �����={d_wins:.3f}, �����={draws:.3f}")

    plt.plot(strategies, player_win_rates, marker="o", label="�����")
    plt.plot(strategies, dealer_win_rates, marker="s", label="�����")
    plt.plot(strategies, draw_rates, marker="^", label="�����")
    plt.title("��������: ������ ��� ������ ���������� ������")
    plt.xlabel("����� (��������� ������)")
    plt.ylabel("���� �������")
    plt.legend()
    plt.show()
