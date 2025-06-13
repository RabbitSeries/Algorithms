# Review

- Simulation: `Queue Problem`, `Geometry`, `Date Calculation`, `String number add/multiply`, `Rank calculation`
- Datastructure: `Tree Traversal Order Transform`
- Graph: `Deepest nodes`
- DP: `Maximun SubSequence Sum`, `0/1 Package`, `Tree Dependency DP`

## Simulation

### Queue Problem

- 1014
- 1017
- 1026

```cpp
    q.push( max( minFinishTime, arriveTime ) + neededTime );            // The service time is the maximun of last finishtime and the arrival time of the customer.
    totalWaitedSeconds += max( minFinishTime, arriveTime ) - arriveTime;// Service time - arrvice time = waited time
```

### Num digits problem

- A1060 How to trim string number's zero-prefix and some dogshit boundary condition.
- A1065 climits

### Date Calculation

```cpp

```

## DataStructure

## Graph

- A1021 : Deepest node problem

## DP

- A1068: 0/1 DP + Greedy print package
