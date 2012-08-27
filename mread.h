#ifndef MREAD_H
#define MREAD_H

struct mread_pool;

/**
 * 创建一个数据缓冲池
 * @param  port   监听的端口
 * @param  max    最大同时连接数
 * @param  buffer 缓冲池大小（传0时会默认创建1M字节的空间）
 * @return 返回缓冲池结构指针
 */
struct mread_pool * mread_create(int port , int max , int buffer);

/**
 * 释放数据缓冲池
 * @param m 缓冲池结构指针
 */
void mread_close(struct mread_pool *m);


/**
 * 获取有数据可读的连接id
 * @param  m       缓冲池结构指针
 * @param  timeout 连接过期时间（传-1时不考虑过期），单位：毫秒
 * @return 返回一个有数据可以读的连接id；或者返回-1，表示没有连接可读
 */
int mread_poll(struct mread_pool *m , int timeout);

/**
 * 从有数据可读的连接获取数据
 * @param  m    缓冲池结构指针
 * @param  size 读取的数据大小
 * @return 读取的数据量
 */
void * mread_pull(struct mread_pool *m , int size);

/**
 * 当你使用完mread_pull返回的数据时，那你必须调用mread_yield来释放空间
 * 不然，你会在下次调用mread_poll时这些数据依然会被mread_pull获得
 * @param m 缓冲池结构指针
 */
void mread_yield(struct mread_pool *m);

/**
 * 检测连接是否关闭，如果是关闭的返回1
 * @return 连接关闭时返回1，否则返回0
 */
int mread_closed(struct mread_pool *m);


/**
 * 关闭一个连接
 * @param m  缓冲池结构指针
 * @param id 连接id
 */
void mread_close_client(struct mread_pool *m, int id);

/**
 * 通过连接id获得连接的socket fd，你可以用它来发送数据
 * @param  m  缓冲池结构指针
 * @param  id 连接id
 * @return 连接的嵌套字描述符，socket fd
 */
int mread_socket(struct mread_pool *m , int id);

#endif
