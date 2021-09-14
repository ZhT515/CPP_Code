#include <iostream>
#include <vector>

using namespace std;

namespace Zht
{
  template <class T>      //仿函数，构造对象
  struct less
  {
    bool operator()(const T& l, const T& r)   
    {
      return l < r;
    }
  };

  template <class T>
  struct greater
  {
    bool operator()(const T& l, const T& r)
    {
      return l > r;
    }
  };

  template <class T, class Container = vector<T>, class Compare = less<T>>
  class priority_queue            //优先队列本质上时堆，默认建大堆
  {
    public:
    void AdjustUp(size_t child)   //建堆
    {
      Compare com;

      size_t parent = (child - 1) / 2;      //父节点是子节点的 - 1  /2
      
      while(child > 0)      //子节点到堆顶结束
      {
       // if(_con[parent] > _con[child])
        if(com(_con[parent], _con[child]))    //用了重载的（）
        {
          swap(_con[parent], _con[child]);
          child = parent;
          parent = (child - 1) / 2; 
        }
        else                  //小于交换，不小于结束建堆
        {
          break;
        }
      }
    }

    void push(const T& x)
    {
      _con.push_back(x);
      AdjustUp(_con.size() - 1);        //最后一节点，即插入的节点的序号
    }

    void AdjustDown(size_t parent)      //向下建堆
    {
      Compare com;

      size_t child = parent * 2 + 1;
      
      while(child < _con.size())
      {
        //if(child + 1 < _con.size() && _con[child] > _con[child + 1])    //确定左右最小的子节点
        if(child + 1 < _con.size() && com(_con[child], _con[child + 1]))    //确定左右最小的子节点
        {
            ++child;
        }

        //if(_con[parent] > _con[child])
        if(com(_con[parent], _con[child]))
        {
          swap(_con[parent], _con[child]);
          parent = child;
          child = parent * 2 + 1;
        }
        else 
        {
          break;
        }
      }
    }
    void pop()
    {
      swap(_con[0], _con[_con.size() - 1]);   //堆顶与最后一个节点交换，方便排序
      _con.pop_back();
      AdjustDown(0);      //从堆顶重新向下建堆
    }

    T top()
    {
      return _con[0];
    }

    size_t size()
    {
      return _con.size();
    }

    bool empty()
    {
      return _con.empty();
    }

    private:
      Container _con;

  };
}
