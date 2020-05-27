#ifndef _GRID_H_
#define _GRID_H_

#include <QVector>
#include <QString>

#include <FieldFlags.h>

using GridType = QVector<int>;


class QFile;

class GridGenerator
{
public:
    GridGenerator();
    virtual ~GridGenerator() {}

    virtual void init();
    virtual void generate();

    size_t size_grid() const;
    size_t size_elements() const;

    void setWidth(int width);
    void setHeight(int height);
    void setLoaderPlayers(int LoaderPlayers);
    void setCargos(int cargos);
    void setCargosDestination(int cargosDst);
    void setBarriers(int barriers);

    int getWidth() const;
    int getHeight() const;
    int getEmpty() const;
    int getLoaderPlayers() const;
    int getCargos() const;
    int getCargosDestination() const;
    int getBarriers() const;

    GridType getGrid() const;

protected:
    int m_width;
    int m_height;
    int m_nLoaderPlayers;
    int m_nCargos;
    int m_nCargosDst;
    int m_nBarriers;
    GridType m_grid;

    virtual void fill(int value, int count) = 0;

    void setValue(int row, int column, int value);
    int getValue(int row, int column) const;
};


class RandomGridGenerator : public GridGenerator
{
protected:
    void fill(int value, int count) override;
};

// Grid generator for debugging
class TestGridGenerator : public GridGenerator
{
public:
    void generate() override;
protected:
    void fill(int value, int count) override;
private:
    void grid5x5();
    void grid10x10();
    void grid15x15();
};

class GridMazes : public GridGenerator
{
public:
    GridMazes(QString filename);
    ~GridMazes();

    void init() override;
    void generate() override;

    void next();
    void previous();

    int getCurrentMaze() const;
protected:
    void fill(int value, int count) override;
private:
    QFile *m_pFile;
    int m_currMaze;
    int m_lastMaze;

    bool readGrid(int mazeNumber);
};

#endif // !_GRID_H_

