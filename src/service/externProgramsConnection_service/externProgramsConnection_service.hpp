#ifndef _EXTERN_PROGRAMS_CONNECTION_SERVICE_HPP_
#define _EXTERN_PROGRAMS_CONNECTION_SERVICE_HPP_

#include <vector>
using namespace std;

class ExternProgramsConnection_service {
    private:
        string generatePyctures_URL;
        vector<string> generatePyctures_entryParams;

    public:
        ExternProgramsConnection_service(string generatePicture_URL);
        ~ExternProgramsConnection_service();
    
        bool executeCommand(string url);
        bool executeCommand();



        //********************************************************
        // ZONA DE DEFINICIÓN DE MÉTODOS DE ACCESO A LAS VARIABLES
        //********************************************************
        string get_generatePyctures_URL();
        void set_generatePyctures_URL(string data);

        vector<string>& get_generatePyctures_entryParams();
        void set_generatePyctures_entryParams(vector<string>& data);


};

#endif
