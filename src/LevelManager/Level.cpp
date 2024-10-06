#include "Level.h"

#include <cassert>

Grid::Grid(int chunk_col, int chunk_row) :
    w_chunks(chunk_col),
    h_chunks(chunk_row),
    w_cell(w_chunks*chunk_size),
    h_cell(h_chunks*chunk_size)
    {
        _data.resize(w_cell*h_cell,2);
    }

Grid::Grid(Grid&& oth):
    w_chunks(oth.w_chunks),
    h_chunks(oth.h_chunks),
    w_cell(w_chunks*chunk_size),
    h_cell(h_chunks*chunk_size),
    _data(std::move(oth._data))
    {}

Grid& Grid::operator=(Grid&& r)
{
    if(this == &r)
        return *this;

    w_chunks = r.w_chunks;
    h_chunks = r.h_chunks;
    w_cell = r.w_cell;
    h_cell = r.h_cell;

    _data = std::move(r._data);
    return *this;
}

int& Grid::at(int x, int y,int ch_x, int ch_y)
{
    assert(x < w_chunks);
    assert(y < h_chunks);
    assert(ch_x < chunk_size);
    assert(ch_y < chunk_size);

    return _data
    [
        y*w_cell*chunk_size +
        ch_y*w_cell +
        x*chunk_size +
        ch_x
    ];
}

int& Grid::at(int x,int y)
{
    assert(x < w_cell);
    assert(y < h_cell);

    return _data
    [
        y*w_cell +
        x
    ];
}

Level::Level():
    ground(0,0),
    collis(0,0)
    {}

Level::Level(int w,int h):
    ground(w,h),
    collis(w,h)
    {}

Level::Level(Level&& oth):
    ID(oth.ID),
    ground(std::move(oth.ground)),
    collis(std::move(oth.collis)),
    ents(std::move(oth.ents)),
    animated(std::move(oth.animated)),
    units(std::move(oth.units))
    {
        //thisis no-valid flag
        oth.ID = BUILD_NEW_LVL;
    }

Level& Level::operator=(Level&& r)
{
    if(this == &r)
        return *this;

    ID = r.ID;
    //thisis no-valid flag
    r.ID = BUILD_NEW_LVL;

    ground = std::move(r.ground);
    collis = std::move(r.collis);
    ents = std::move(r.ents);
    animated = std::move(r.animated);
    units = std::move(r.units);

    return *this;
}

Level::~Level()
{
    for (auto &&i : ents)
        delete i;
}