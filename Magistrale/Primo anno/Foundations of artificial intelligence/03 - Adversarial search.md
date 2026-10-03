In many problems where there is an **opponent**, certain operators are beyond our control, and we cannot search the entire space for an optimal path, also because the opponent may make a move which makes any discovered path, obsolete.

When the opponent is **unpredictable**, the solution is a strategy, where we specify a move for every possible opponent reply, and due to some eventual time limits, we must **approximate**.

### Type of games
We restrict our analysis to a very specific set of games: <u>2-player zero-sum discrete finite deterministic games of perfect information</u>.
- **Zero-sum**: one player's gain is equal to the other player's loss (e.g. one wins, the other loses)
- **Discrete**: every game state and decision is a discrete value
- **Finite**: only a finite number of states and decisions
- **Deterministic**: no die rolls
- **Perfect information**: both players see the state, and each decision is made sequentially

### Game tree search
A game tree is a structure that represents all possible moves and their consequences, the key components of this structure are:
- **Initial state**: starting point of the game
- **Operators**: legal moves that a player can make from a given position
- **Goal states**: end positions of a game (e.g. win, loss or draw)
- **Scoring function**: assigns a heuristic value to each state, in order to evaluate how good or bad the position is

### Minimax
Let's consider a game with a small full game tree, for example tic-tac-toe.
In this case we can build the entire game tree with a [[01 - Blind search#Depth-First search|DFS]], and assume that both players play optimally.

While exploring the tree we can apply the utility function to each terminal state, if it is our turn we will choose the node with max utility, while if it is the opponent's turn, we assume that he's going to pick the node with the max utility for him, so the minimum utility for us.

>[!Tip] The concept
>The idea is to pick the best next move against our best move.

![[Minimax.png|400]]

The properties of the **minimax** algorithm are:
- **Complete**: yes, if the tree is finite
- **Optimal**: yes, if the opponent plays optimally, otherwise no, because it may not exploit the mistake, and take a safer (and longer) path
- **Time complexity**: $O(b^d)$
- **Space complexity**: $O(db)$
#### $\alpha-\beta$ pruning
The problem with minimax algorithm, is that <u>the number of game states is exponential in the number of moves</u>, so for example, in chess, considering the analyzed time complexity, we would have $b\approx 35$ and $d\approx 40$ for "reasonable" games, which is infeasible.

$\alpha-\beta$ pruning proposes to compute the correct minimax algorithm decision <u>without looking at every node in the game tree</u>.
- $\alpha$: best value for max so far, initialized to $-\infty$
- $\beta$: best value for min so far, initialized to $\infty$

![[Alpha-beta pruning.png|500]]

1. We start by exploring the game tree with a DFS
2. Set $\alpha$ to the maximum (and $\beta$ to the minimum) value that has been found from the current node value $v$ up until the root
3. Before exploring another child we evaluate the current node $\beta\leq\alpha$, and if true, we prune the unexplored children

Imagining being the MAX player in the node $N_5$, we can avoid exploring other children after visiting the left one, because we already know that the opponent will never pick this node, since he knows that we would pick a better alternative than what we currently have (i.e. $7$ instead of $4$).


>[!Info] Expect-Minimax
>For non-deterministic games, where probabilities are involved, it is possible to compute the expected value of each node, and then apply the same minimax logic.
>
>Note that in this case pruning is risky because each child contributes to the expected value.

