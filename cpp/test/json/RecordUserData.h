#ifndef __RECORD_USER_DATA__
#define __RECORD_USER_DATA__

class RecordUserData {
public:
    RecordUserData();
    ~RecordUserData();

    int setUserData(const char *info);
    const char *getUserData();

private:
    char m_musicCheckSum[64];
    char m_phoneCheckSum[64];
    char m_phoneHistoryCheckSum[64];

    char *m_music;
    int m_musicSize;

    char *m_phone;
    int m_phoneSize;

    char *m_phoneHistory;
    int m_phoneHistorySize;


    char *m_userData;
    int m_userDataSize;

};


#endif
