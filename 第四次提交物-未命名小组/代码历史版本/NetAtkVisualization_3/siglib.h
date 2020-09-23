#ifndef SIGLIB_H
#define SIGLIB_H

/*
    标识程序运行状况的信号量
*/

enum Signal
{
    Signal_normal,

    Signal_unchange,
    Signal_over_delete,
    Signal_existed,

    Signal_new_Node,
    Signal_new_Port,
    Signal_new_
};

#endif // SIGLIB_H
