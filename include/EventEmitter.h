#ifndef EVENT_EMITTER
#define EVENT_EMITTER

typedef void (*CB)(int &);

#define MAX_QTY_CB 5

template <typename T>
class EventEmitter
{
private:
    int eventQty = int(T::SIZE) * MAX_QTY_CB;
    CB arr[int(T::SIZE) * MAX_QTY_CB];

public:
    EventEmitter()
    {
        for (int i = 0; i < eventQty; i++)
        {
            arr[i] = NULL;
        }
    }
    void addObserver(T &&event, CB callBack)
    {
        int start = (int)event * MAX_QTY_CB;
        for (int i = start; i < start + MAX_QTY_CB; i++)
        {
            if (!arr[i])
            {
                arr[i] = callBack;
                break;
            }
        }
    }

    void removeObserver(T &&event)
    {
        int start = (int)event * MAX_QTY_CB;
        for (int i = start; i < start + MAX_QTY_CB; i++)
        {
            arr[i] = NULL;
        }
    }

    void dispatchEvent(T &&event)
    {

        int start = ((int)event * MAX_QTY_CB);

        for (int i = start; i < start + MAX_QTY_CB; i++)
        {
            if (arr[i] != NULL)
            {
                arr[i]();
            }
        }
    }
};

#endif
