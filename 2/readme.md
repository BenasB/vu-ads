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