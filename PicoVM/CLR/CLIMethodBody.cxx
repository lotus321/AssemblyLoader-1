#include <sstream>
#include <iomanip>

#include "CLIMethodBody.hxx"
#include "HexStr.hxx"

using namespace std;

string ExceptionClause::str() const {
    stringstream ss;
    ss << "ExceptionClause(tryOffset=" << hex << tryOffset << " tryLength=" << dec << tryLength << " handlerOffset=" << hex << handlerOffset << " handlerLength=" << dec << handlerLength << " classTokenOrFilterOffset=" << hex << classTokenOrFilterOffset << ")";
    return ss.str();
}

string MethodBody::str(bool fPrintBody) const {
    stringstream ss;
    ss << "MethodBody(" << endl;
    if (data.size() != 0) {

        ss << " maxStack=" << dec << maxStack << endl;

        if (localVarSigs.size() > 0) {
            ss << " localVarSigs=(" << hex << setfill('0') << endl;
            for (const auto signature : localVarSigs) {
                ss << "  " << setw(2) << signature << endl;
            }
            ss << " )" << endl;
        }
        ss << " initLocals=" << dec << initLocals << endl;

        if (exceptions.size() != 0) {
            ss << " Exceptions(" << endl;
            for(const auto& exception : exceptions) {
                ss << "   " << exception.str() << endl;
            }
            ss << " )" << endl;
        }

        if (fPrintBody) {
            ss << " Body(" << endl 
            << "  " << HexStr(data.cbegin(), data.cend(), true) << endl 
            << " )" << endl; 
        } else {
            ss << " bodySize=" << dec << data.size() << endl; 
        }
    }

    ss << ")";

    return ss.str();
}

string MethodBody::str() const {
    return str(false);
}

MethodBody & MethodBody::operator=(const MethodBody & other)
{
    MethodBody(other).swap(*this);
    return *this;
}

void MethodBody::swap(MethodBody & other) noexcept
{
    ::swap(data, other.data);
    ::swap(localVarSigs, other.localVarSigs);
    ::swap(exceptions, other.exceptions);
    ::swap(maxStack, other.maxStack);
    ::swap(initLocals, other.initLocals);
}

MethodBody::~MethodBody() noexcept
{
}
