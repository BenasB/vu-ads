## 12 dominating knights

> 7) Išdėstyti šachmatų lentoje 12 žirgų, kad kiekvienas langelis būtų kontroliuojamas bent vieno iš jų.

Reference: https://stackoverflow.com/questions/36527317/12-dominating-knights-puzzle-backtracking

Board:
- 0 - not attacked
- 1 - attacked
- 2 - knight

### Time complexity:

If we consided `n = board size` (normally 8) and `m = knight count` (in 8x8 board this is 12)

- Bruteforce: n^(2m) combinations ~ O(n^m). For 8x8 board with 12 knights different cominations = 8^(2*12) = 2.8147498e+14
- Backtracking: definetely less than O(n^m) but can't determine because it depends on 2 variables which correlate with each other
  - Best case: O(m) ?
  - Worst case: O(2^m) ?

### LFF:

| Date       | From  | To    | Disturbances | Time  | Activity      | Comments                                                                    |
| ---------- | ----- | ----- | ------------ | ----- | ------------- | --------------------------------------------------------------------------- |
| 2022-04-03 | 13:00 | 15:49 |              | 02:49 | Programming   | Added bruteforce implementation                                             |
| 2022-04-03 | 23:00 | 23:15 |              | 00:15 | Programming   | Attack map generation                                                       |
| 2022-04-04 | 22:30 | 22:58 |              | 00:28 | Programming   | Changed knight move combination to for loops and getLowestAttackabilityTile |
| 2022-04-05 | 16:50 | 17:52 |              | 01:02 | Programming   | Implemented backtracking with recursion, solutions found                    |
| 2022-04-05 | 17:52 | 18:11 |              | 00:18 | Documentation | Determined bruteforce time complexity and combinations                      |
| 2022-04-05 | 18:11 | 19:52 |              | 01:40 | Documentation | Failed to determine backtracking time complexity                            |
| 2022-04-05 | 19:52 | 20:08 |              | 00:16 | Programming   | Added timer                                                                 |