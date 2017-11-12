// 串的块链存储表示

#define CHUNKSIZE 80
typedef struct Chunk
{
	char ch[CHUNKSIZE];
	struct Chunk *next;
}Chunk;

typedef struct 
{
	Chunk *head, *tail;		// 串的头指针，尾指针
	int curlen;				// 串的当前长度
}LString;