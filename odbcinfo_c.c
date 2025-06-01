// ODBC info en C

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>

int main() {
    SQLHENV hEnv;
    SQLRETURN ret;
    SQLCHAR driverDesc[256];
    SQLSMALLINT driverDescLen;
    SQLCHAR driverAttr[256];
    SQLSMALLINT driverAttrLen;

    // Aloja el entorno ODBC
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        printf("Error al asignar el handle del entorno.\n");
        return 1;
    }

    // Establece la versión ODBC
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        printf("Error al establecer la versión ODBC.\n");
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return 1;
    }

    printf("Controladores ODBC instalados:\n\n");

    // Recorre los controladores ODBC
    ret = SQLDrivers(hEnv, SQL_FETCH_FIRST, driverDesc, sizeof(driverDesc), &driverDescLen,
                     driverAttr, sizeof(driverAttr), &driverAttrLen);

    while (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        printf("Nombre del controlador: %s\n", driverDesc);
        printf("Atributos: %s\n\n", driverAttr);

        ret = SQLDrivers(hEnv, SQL_FETCH_NEXT, driverDesc, sizeof(driverDesc), &driverDescLen,
                         driverAttr, sizeof(driverAttr), &driverAttrLen);
    }

    // Libera el entorno
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}
