#ifndef MREAD_RINGBUFFER_H
#define MREAD_RINGBUFFER_H

/**
 * 缓冲器结构
 */
struct ringbuffer;

/**
 * 数据块结构
 */
struct ringbuffer_block
{
	int length; // 数据块长度
	int offset; // 数据块头指针在缓冲区的偏移量
	int id;     // ID
	int next;   // 下一个数据块位置
};

/**
 * 创建新的缓冲器
 * @param  size 缓冲区大小
 * @return 缓冲器指针
 */
struct ringbuffer * ringbuffer_new(int size);

/**
 * 销毁缓冲器
 * @param rb 缓冲器指针
 */
void ringbuffer_delete(struct ringbuffer * rb);

/**
 * 连接两个数据块
 * @param rb   缓冲器指针
 * @param prev 前一个数据块
 * @param next 后一个数据块
 */
void ringbuffer_link(struct ringbuffer *rb, struct ringbuffer_block * prev, struct ringbuffer_block * next);

/**
 * 改变缓冲器大小
 * @param  rb   缓冲器指针
 * @param  size 缓冲区新尺寸
 * @return 缓冲器指针
 */
struct ringbuffer_block * ringbuffer_alloc(struct ringbuffer * rb, int size);

/**
 * 
 * @param  rb 缓冲器指针
 * @return 
 */
int ringbuffer_collect(struct ringbuffer * rb);

/**
 * 改变制定数据块的大小
 * @param rb   缓冲器指针
 * @param blk  数据块
 * @param size 数据块新尺寸
 */
void ringbuffer_resize(struct ringbuffer * rb, struct ringbuffer_block * blk, int size);

/**
 * 释放一个数据块内存
 * @param rb  缓冲器指针
 * @param blk 数据块
 */
void ringbuffer_free(struct ringbuffer * rb, struct ringbuffer_block * blk);

/**
 * 
 * @param  rb   缓冲器指针
 * @param  blk  数据块
 * @param  size 
 * @return 
 */
int ringbuffer_data(struct ringbuffer * rb, struct ringbuffer_block * blk, int size, int skip, void **ptr);

/**
 * 复制一个数据块到另一个数据块
 * @param  rb   缓冲器指针
 * @param  from 复制源
 * @param  skip 
 * @param  to   目标数据块
 * @return 
 */
void * ringbuffer_copy(struct ringbuffer * rb, struct ringbuffer_block * from, int skip, struct ringbuffer_block * to);

/**
 * 
 * @param  rb   缓冲器指针
 * @param  blk  数据块
 * @param  skip 
 * @return 
 */
struct ringbuffer_block * ringbuffer_yield(struct ringbuffer * rb, struct ringbuffer_block *blk, int skip);


/**
 * 输出缓冲器信息
 * @param rb 缓冲器指针
 */
void ringbuffer_dump(struct ringbuffer * rb);

#endif

