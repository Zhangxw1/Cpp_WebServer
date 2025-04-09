#include "../Cmdoule.h"
#include <mysql/mysql.h>




class Cmysql
{
private:
    MYSQL mysql_conn;

    // 数据库连接句柄
    MYSQL *DB;

public:
    struct InsertModel
    {
        std::string Value; // 值
        std::string Key;   // 字段名
    };

    // 保存获取的结果集
    SQLDATA ResultData;
    Cmysql();
    void InitMysql(const char *address, const char *user, const char *password, const char *DbName, int port);

    void ConditionSearch(std::string TableName, std::string Condition, std::string Vaule, ...);
    void CloseMysql();
    void GetResult();
    void OutResultTerminal();
    void InsertData(std::string TableName, std::unordered_map<std::string, std::string> in);
};

class CmysqlPool
{
public:
    int n;                           // 数据库连接池数量
    //std::deque<std::string> TaskSql; // 数据库执行任务队列

    SQLDATA SubmitTask(std::string sql); //返回值为std::unordered_map<std::string, std::vector<std::string>>的函数声明   参数为要执行的sql语句
	/*SQLDATA返回值示例
	{
    "name":  ["Alice", "Bob"],   // 字段"name"的所有值
    "age":   ["25", "30"],       // 字段"age"的所有值
    "email": ["a@test.com", "b@test.com"]
	}
	*/
    void InitCmysqlPool(int num, const char *address,       \
     const char *user, const char *password, const char *DbName, int port);

    static CmysqlPool* AcquireCmysqlPool();
private:
    CmysqlPool(){};
    std::deque<MYSQL *> DBList; // 存放数据库连接池数据库句柄（deque双端队列）
    std::mutex DBList_lock;
    MYSQL *GetMysqlDB();

    SQLDATA GetResultPool(MYSQL *handle);
};

