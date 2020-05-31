#include <iostream>
#include <vector>

#include <wiredtiger.h>

void read_from_file();
void write_to_file();

int main(int argc, char const *argv[])
{
    read_from_file();
}

void write_to_file(){
    using namespace std;

    vector<string> keys;
    vector<string> values;

    keys.push_back("genji");
    values.push_back("1");

    keys.push_back("winston");
    values.push_back("2");

    keys.push_back("mei");
    values.push_back("3");

    WT_CONNECTION *wt_conn;
    WT_SESSION *session;
    WT_CURSOR *cursor;
    
    
    const char * database_dir_path ="/Users/peiyulin/Desktop/wiredtiger_c++_api/wiredTiger_data";

    int open_return_code =  wiredtiger_open(database_dir_path,NULL,"create,cache_size=100M",&wt_conn);
    
    cout << "open_return_code" << open_return_code <<endl;

    int open_session_code = wt_conn->open_session(wt_conn,NULL,NULL,&session);

    cout << "open_session_code" << open_session_code <<endl;

    int session_create_code = session->create(session,"table:overwatch","key_format=S,value_format=S");

    cout << "session_create_code" << session_create_code <<endl;

    session->open_cursor(session,"table:overwatch", NULL, NULL, &cursor);

    for(int i =0;i<keys.size();i++){
        auto key = keys.begin()+i;
        auto value = values.begin()+i;

        cursor->set_key(cursor, key->c_str());        /* Insert a record. */
        cursor->set_value(cursor, value->c_str());
        int ret = cursor->insert(cursor);

        if(ret == 0){
            cout << "Inserted" << endl;
        }else{
            cout << "Failed to insert" << endl;
        }

    }

    int close_ret = wt_conn->close(wt_conn,NULL);

    cout << "close_ret" << close_ret <<endl;

    return;
}


void read_from_file() {
    using namespace std;

    WT_CONNECTION *wt_conn;
    WT_SESSION *session;
    WT_CURSOR *cursor;
    
    
    const char * database_dir_path ="/Users/peiyulin/Desktop/wiredtiger_c++_api/wiredTiger_data";

    int open_return_code =  wiredtiger_open(database_dir_path,NULL,"create,cache_size=100M",&wt_conn);
    
    cout << "open_return_code" << open_return_code <<endl;

    int open_session_code = wt_conn->open_session(wt_conn,NULL,NULL,&session);

    cout << "open_session_code" << open_session_code <<endl;

    int session_create_code = session->create(session,"table:overwatch","key_format=S,value_format=S");

    cout << "session_create_code" << session_create_code <<endl;

    session->open_cursor(session,"table:overwatch", NULL, NULL, &cursor);

    int ret = 0;

    char * key,*value;

    //get all key values
    // while ((ret = cursor->next(cursor)) == 0) {
    //             ret = cursor->get_key(cursor, &key);
    //             ret = cursor->get_value(cursor, &value);
    //             cout <<"Got record: "<<key<<"="<<value<<endl;
    // }

    //search a key
    const char * search_key = "genji";
    cursor->set_key(cursor,search_key);
    cursor->search(cursor);
    cursor->get_value(cursor, &value);
    cout <<"Got record: "<<search_key<<"="<<value<<endl;


    int close_ret = wt_conn->close(wt_conn,NULL);

    cout << "close_ret" << close_ret <<endl;

    return;
}