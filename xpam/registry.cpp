#include "registry.h"
#include "util.h"

Registry::Registry() {}

QString Registry :: getInstallPath() {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_READ | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        QString s=Registry::getRegString(&reg, "InstallPath");
        reg.Close();
        return s;
    }
    else {
        return "ERROR";
    }
}

QString Registry :: getInstallPathX() {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_READ | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        QString s=Registry::getRegString(&reg, "InstallPathX");
        reg.Close();
        return s;
    }
    else {
        return "ERROR";
    }
}

QString Registry :: getW3dir() {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Eurobattle.net"), KEY_READ | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        QString s=Registry::getRegString(&reg, "w3dir");
        reg.Close();
        return s;
    }
    else {
        return "ERROR";
    }
}

QString Registry :: getEuroPath() {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Eurobattle.net"), KEY_READ | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        QString s=Registry::getRegString(&reg, "europath");
        reg.Close();
        return s;
    }
    else return Util::getLastErrorMsg();
}

int Registry :: getPatchVersion() {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Eurobattle.net"), KEY_READ | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        DWORD s=Registry::getRegDWORD(reg, "patch");
        reg.Close();
        return (int)s;
    }
    else return -1;
}

QString Registry :: getGproxyReady() {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Eurobattle.net"), KEY_READ | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        QString s=Registry::getRegString(&reg, "gproxy_ready");
        reg.Close();
        return s;
    }
    else return "";
}

QString Registry :: getRegString(CRegKey * reg, QString name) {
    wchar_t * szBuffer = new wchar_t[MAX_PATH];
    ULONG bufsize=MAX_PATH;
    std::wstring w=name.toStdWString();

    DWORD s = reg->QueryStringValue(w.c_str(), szBuffer, &bufsize);
    if (s == ERROR_SUCCESS) {
        QString s=QString::fromWCharArray(szBuffer);
        delete[] szBuffer;
        return s;
    }
    else {
        return "";
    }
}

DWORD Registry :: getRegDWORD(CRegKey reg, QString name) {
    DWORD buf;
    std::wstring w = name.toStdWString();
    DWORD s = reg.QueryDWORDValue(w.c_str(), buf);
    if (s == ERROR_SUCCESS) {
        return buf;
    }
    else {
        return -1;
    }
}

bool Registry :: setRegString(CRegKey reg, QString name, QString value) {
    std::wstring w1=name.toStdWString();
    std::wstring w2=value.toStdWString();
    DWORD s = reg.SetStringValue(w1.c_str(), w2.c_str(), REG_SZ);
    if (s==ERROR_SUCCESS) {
        return true;
    }
    else {
        return false;
    }
}

bool Registry :: setRegDWORD(CRegKey reg, QString name, DWORD value) {
    std::wstring w=name.toStdWString();
    DWORD s = reg.SetDWORDValue(w.c_str(), value);
    if (s==ERROR_SUCCESS) {
        return true;
    }
    else {
        return false;
    }
}

DWORD Registry :: setGateways() {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_WRITE | KEY_WOW64_64KEY)==ERROR_SUCCESS){
        wchar_t lines[21][255]= {
            _T("1008"),
            _T("04"),
            _T("uswest.battle.net"),
            _T("8"),
            _T("Lordaeron (U.S. West)"),
            _T("useast.battle.net"),
            _T("6"),
            _T("Azeroth (U.S. East)"),
            _T("asia.battle.net"),
            _T("-9"),
            _T("Kalimdor (Asia)"),
            _T("europe.battle.net"),
            _T("-1"),
            _T("Northrend (Europe)"),
            _T("server.eurobattle.net"),
            _T("-1"),
            _T("Eurobattle.net"),
            _T("localhost"),
            _T("-1"),
            _T("Eurobattle.net GProxy"),
            _T("")
        };
        size_t totalSize=0;
        for (int i=0; i<21; i++) {
            totalSize+=(wcslen(lines[i])+1)*sizeof(wchar_t);
        }

        LPBYTE pString;
        pString = static_cast<LPBYTE>(malloc(totalSize));

        size_t offset=0;
        for (int i=0; i<21; i++) {
            size_t len=(wcslen(lines[i])+1)*sizeof(wchar_t);
            memcpy(pString+offset, lines[i], len);
            offset+=len;
        }        

        DWORD r = RegSetValueEx(reg, _T("Battle.net Gateways"), 0, REG_MULTI_SZ, pString, totalSize);

        reg.Close();
        delete pString;

        return r;
    }
    else {
        return GetLastError();
    }
    return GetLastError();
}

DWORD Registry :: setGproxyGateways() {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_WRITE | KEY_WOW64_64KEY)==ERROR_SUCCESS){
        wchar_t lines[21][255]= {
            _T("1008"),
            _T("05"),
            _T("uswest.battle.net"),
            _T("8"),
            _T("Lordaeron (U.S. West)"),
            _T("useast.battle.net"),
            _T("6"),
            _T("Azeroth (U.S. East)"),
            _T("asia.battle.net"),
            _T("-9"),
            _T("Kalimdor (Asia)"),
            _T("europe.battle.net"),
            _T("-1"),
            _T("Northrend (Europe)"),
            _T("server.eurobattle.net"),
            _T("-1"),
            _T("Eurobattle.net"),
            _T("localhost"),
            _T("-1"),
            _T("Eurobattle.net GProxy"),
            _T("")
        };
        size_t totalSize=0;
        for (int i=0; i<21; i++) {
            totalSize+=(wcslen(lines[i])+1)*sizeof(wchar_t);
        }

        LPBYTE pString;
        pString = static_cast<LPBYTE>(malloc(totalSize));

        size_t offset=0;
        for (int i=0; i<21; i++) {
            size_t len=(wcslen(lines[i])+1)*sizeof(wchar_t);
            memcpy(pString+offset, lines[i], len);
            offset+=len;
        }

        DWORD r = RegSetValueEx(reg, _T("Battle.net Gateways"), 0, REG_MULTI_SZ, pString, totalSize);

        reg.Close();
        delete pString;

        return r;
    }
    else {
        return GetLastError();
    }
    return GetLastError();
}

bool Registry::setPatchVersion(int version) {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        bool r = Registry::setRegDWORD(reg, "patch", (DWORD)version);
        //RegFlushKey(HKEY_CURRENT_USER);
        reg.Close();
        return r;
    }
    return false;
}

bool Registry::delGM() {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software"), KEY_ALL_ACCESS | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        DWORD ret = reg.RecurseDeleteKey(_T("Garenamaster"));
        reg.Close();
        if (ret==ERROR_SUCCESS) return true;
        else return false;
    }
    return false;
}

bool Registry::setW3dir(QString w3dir) {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        bool r = this->setRegString(reg, "w3dir", w3dir);
        reg.Close();
        return r;
    }
    return false;
}

bool Registry::setInstallPath(QString w3dir) {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_WRITE | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        bool r = this->setRegString(reg, "InstallPath", w3dir);
        reg.Close();
        return r;
    }
    return false;
}

bool Registry::setInstallPathX(QString w3dir) {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_WRITE | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        bool r = this->setRegString(reg, "InstallPathX", w3dir);
        reg.Close();
        return r;
    }
    return false;
}

bool Registry::setDefaultTFT() {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_WRITE | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        bool r = this->setRegDWORD(reg, "Preferred Game Version", 1);
        reg.Close();
        return r;
    }
    return false;
}
