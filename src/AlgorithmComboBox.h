#ifndef ALGORITHMCOMBOBOX_H
#define ALGORITHMCOMBOBOX_H

#include <QComboBox>
#include "AbstractGraph.h"

class AlgorithmComboBox : public QComboBox {
    Q_OBJECT

public:
    AlgorithmComboBox();
    void showPopup() override;

private:
    struct Algorithm {
        QString name;
        algorithmType type;
    };
    const QList<Algorithm> algorithms = {{"DFS", dfs}, {"BFS", bfs}, {"Dijkstra's", dijkstras}, {"Prim's MST", primsmst},
                                       {"Hamiltonian Cycle", hamcycle}};
};

#endif // ALGORITHMCOMBOBOX_H
