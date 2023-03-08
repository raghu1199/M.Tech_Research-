//
// Generated file, do not edit! Created by opp_msgtool 6.0 from MyMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "MyMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(MyMessage)

MyMessage::MyMessage(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

MyMessage::MyMessage(const MyMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

MyMessage::~MyMessage()
{
    delete [] this->hosts;
    delete [] this->nodedata;
}

MyMessage& MyMessage::operator=(const MyMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void MyMessage::copy(const MyMessage& other)
{
    this->source = other.source;
    this->destination = other.destination;
    this->hopecount = other.hopecount;
    delete [] this->hosts;
    this->hosts = (other.hosts_arraysize==0) ? nullptr : new int[other.hosts_arraysize];
    hosts_arraysize = other.hosts_arraysize;
    for (size_t i = 0; i < hosts_arraysize; i++) {
        this->hosts[i] = other.hosts[i];
    }
    delete [] this->nodedata;
    this->nodedata = (other.nodedata_arraysize==0) ? nullptr : new int[other.nodedata_arraysize];
    nodedata_arraysize = other.nodedata_arraysize;
    for (size_t i = 0; i < nodedata_arraysize; i++) {
        this->nodedata[i] = other.nodedata[i];
    }
    this->sndata = other.sndata;
    this->type = other.type;
}

void MyMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->source);
    doParsimPacking(b,this->destination);
    doParsimPacking(b,this->hopecount);
    b->pack(hosts_arraysize);
    doParsimArrayPacking(b,this->hosts,hosts_arraysize);
    b->pack(nodedata_arraysize);
    doParsimArrayPacking(b,this->nodedata,nodedata_arraysize);
    doParsimPacking(b,this->sndata);
    doParsimPacking(b,this->type);
}

void MyMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->source);
    doParsimUnpacking(b,this->destination);
    doParsimUnpacking(b,this->hopecount);
    delete [] this->hosts;
    b->unpack(hosts_arraysize);
    if (hosts_arraysize == 0) {
        this->hosts = nullptr;
    } else {
        this->hosts = new int[hosts_arraysize];
        doParsimArrayUnpacking(b,this->hosts,hosts_arraysize);
    }
    delete [] this->nodedata;
    b->unpack(nodedata_arraysize);
    if (nodedata_arraysize == 0) {
        this->nodedata = nullptr;
    } else {
        this->nodedata = new int[nodedata_arraysize];
        doParsimArrayUnpacking(b,this->nodedata,nodedata_arraysize);
    }
    doParsimUnpacking(b,this->sndata);
    doParsimUnpacking(b,this->type);
}

int MyMessage::getSource() const
{
    return this->source;
}

void MyMessage::setSource(int source)
{
    this->source = source;
}

int MyMessage::getDestination() const
{
    return this->destination;
}

void MyMessage::setDestination(int destination)
{
    this->destination = destination;
}

int MyMessage::getHopecount() const
{
    return this->hopecount;
}

void MyMessage::setHopecount(int hopecount)
{
    this->hopecount = hopecount;
}

size_t MyMessage::getHostsArraySize() const
{
    return hosts_arraysize;
}

int MyMessage::getHosts(size_t k) const
{
    if (k >= hosts_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hosts_arraysize, (unsigned long)k);
    return this->hosts[k];
}

void MyMessage::setHostsArraySize(size_t newSize)
{
    int *hosts2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = hosts_arraysize < newSize ? hosts_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        hosts2[i] = this->hosts[i];
    for (size_t i = minSize; i < newSize; i++)
        hosts2[i] = 0;
    delete [] this->hosts;
    this->hosts = hosts2;
    hosts_arraysize = newSize;
}

void MyMessage::setHosts(size_t k, int hosts)
{
    if (k >= hosts_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hosts_arraysize, (unsigned long)k);
    this->hosts[k] = hosts;
}

void MyMessage::insertHosts(size_t k, int hosts)
{
    if (k > hosts_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hosts_arraysize, (unsigned long)k);
    size_t newSize = hosts_arraysize + 1;
    int *hosts2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        hosts2[i] = this->hosts[i];
    hosts2[k] = hosts;
    for (i = k + 1; i < newSize; i++)
        hosts2[i] = this->hosts[i-1];
    delete [] this->hosts;
    this->hosts = hosts2;
    hosts_arraysize = newSize;
}

void MyMessage::appendHosts(int hosts)
{
    insertHosts(hosts_arraysize, hosts);
}

void MyMessage::eraseHosts(size_t k)
{
    if (k >= hosts_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)hosts_arraysize, (unsigned long)k);
    size_t newSize = hosts_arraysize - 1;
    int *hosts2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        hosts2[i] = this->hosts[i];
    for (i = k; i < newSize; i++)
        hosts2[i] = this->hosts[i+1];
    delete [] this->hosts;
    this->hosts = hosts2;
    hosts_arraysize = newSize;
}

size_t MyMessage::getNodedataArraySize() const
{
    return nodedata_arraysize;
}

int MyMessage::getNodedata(size_t k) const
{
    if (k >= nodedata_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)nodedata_arraysize, (unsigned long)k);
    return this->nodedata[k];
}

void MyMessage::setNodedataArraySize(size_t newSize)
{
    int *nodedata2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = nodedata_arraysize < newSize ? nodedata_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        nodedata2[i] = this->nodedata[i];
    for (size_t i = minSize; i < newSize; i++)
        nodedata2[i] = 0;
    delete [] this->nodedata;
    this->nodedata = nodedata2;
    nodedata_arraysize = newSize;
}

void MyMessage::setNodedata(size_t k, int nodedata)
{
    if (k >= nodedata_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)nodedata_arraysize, (unsigned long)k);
    this->nodedata[k] = nodedata;
}

void MyMessage::insertNodedata(size_t k, int nodedata)
{
    if (k > nodedata_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)nodedata_arraysize, (unsigned long)k);
    size_t newSize = nodedata_arraysize + 1;
    int *nodedata2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        nodedata2[i] = this->nodedata[i];
    nodedata2[k] = nodedata;
    for (i = k + 1; i < newSize; i++)
        nodedata2[i] = this->nodedata[i-1];
    delete [] this->nodedata;
    this->nodedata = nodedata2;
    nodedata_arraysize = newSize;
}

void MyMessage::appendNodedata(int nodedata)
{
    insertNodedata(nodedata_arraysize, nodedata);
}

void MyMessage::eraseNodedata(size_t k)
{
    if (k >= nodedata_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)nodedata_arraysize, (unsigned long)k);
    size_t newSize = nodedata_arraysize - 1;
    int *nodedata2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        nodedata2[i] = this->nodedata[i];
    for (i = k; i < newSize; i++)
        nodedata2[i] = this->nodedata[i+1];
    delete [] this->nodedata;
    this->nodedata = nodedata2;
    nodedata_arraysize = newSize;
}

const char * MyMessage::getSndata() const
{
    return this->sndata.c_str();
}

void MyMessage::setSndata(const char * sndata)
{
    this->sndata = sndata;
}

int MyMessage::getType() const
{
    return this->type;
}

void MyMessage::setType(int type)
{
    this->type = type;
}

class MyMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_source,
        FIELD_destination,
        FIELD_hopecount,
        FIELD_hosts,
        FIELD_nodedata,
        FIELD_sndata,
        FIELD_type,
    };
  public:
    MyMessageDescriptor();
    virtual ~MyMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(MyMessageDescriptor)

MyMessageDescriptor::MyMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(MyMessage)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

MyMessageDescriptor::~MyMessageDescriptor()
{
    delete[] propertyNames;
}

bool MyMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MyMessage *>(obj)!=nullptr;
}

const char **MyMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *MyMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int MyMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int MyMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_source
        FD_ISEDITABLE,    // FIELD_destination
        FD_ISEDITABLE,    // FIELD_hopecount
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_hosts
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_nodedata
        FD_ISEDITABLE,    // FIELD_sndata
        FD_ISEDITABLE,    // FIELD_type
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *MyMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "source",
        "destination",
        "hopecount",
        "hosts",
        "nodedata",
        "sndata",
        "type",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int MyMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "source") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destination") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "hopecount") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "hosts") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "nodedata") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "sndata") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "type") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *MyMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_source
        "int",    // FIELD_destination
        "int",    // FIELD_hopecount
        "int",    // FIELD_hosts
        "int",    // FIELD_nodedata
        "string",    // FIELD_sndata
        "int",    // FIELD_type
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **MyMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *MyMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int MyMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    MyMessage *pp = omnetpp::fromAnyPtr<MyMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hosts: return pp->getHostsArraySize();
        case FIELD_nodedata: return pp->getNodedataArraySize();
        default: return 0;
    }
}

void MyMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    MyMessage *pp = omnetpp::fromAnyPtr<MyMessage>(object); (void)pp;
    switch (field) {
        case FIELD_hosts: pp->setHostsArraySize(size); break;
        case FIELD_nodedata: pp->setNodedataArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'MyMessage'", field);
    }
}

const char *MyMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    MyMessage *pp = omnetpp::fromAnyPtr<MyMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string MyMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    MyMessage *pp = omnetpp::fromAnyPtr<MyMessage>(object); (void)pp;
    switch (field) {
        case FIELD_source: return long2string(pp->getSource());
        case FIELD_destination: return long2string(pp->getDestination());
        case FIELD_hopecount: return long2string(pp->getHopecount());
        case FIELD_hosts: return long2string(pp->getHosts(i));
        case FIELD_nodedata: return long2string(pp->getNodedata(i));
        case FIELD_sndata: return oppstring2string(pp->getSndata());
        case FIELD_type: return long2string(pp->getType());
        default: return "";
    }
}

void MyMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    MyMessage *pp = omnetpp::fromAnyPtr<MyMessage>(object); (void)pp;
    switch (field) {
        case FIELD_source: pp->setSource(string2long(value)); break;
        case FIELD_destination: pp->setDestination(string2long(value)); break;
        case FIELD_hopecount: pp->setHopecount(string2long(value)); break;
        case FIELD_hosts: pp->setHosts(i,string2long(value)); break;
        case FIELD_nodedata: pp->setNodedata(i,string2long(value)); break;
        case FIELD_sndata: pp->setSndata((value)); break;
        case FIELD_type: pp->setType(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MyMessage'", field);
    }
}

omnetpp::cValue MyMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    MyMessage *pp = omnetpp::fromAnyPtr<MyMessage>(object); (void)pp;
    switch (field) {
        case FIELD_source: return pp->getSource();
        case FIELD_destination: return pp->getDestination();
        case FIELD_hopecount: return pp->getHopecount();
        case FIELD_hosts: return pp->getHosts(i);
        case FIELD_nodedata: return pp->getNodedata(i);
        case FIELD_sndata: return pp->getSndata();
        case FIELD_type: return pp->getType();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'MyMessage' as cValue -- field index out of range?", field);
    }
}

void MyMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    MyMessage *pp = omnetpp::fromAnyPtr<MyMessage>(object); (void)pp;
    switch (field) {
        case FIELD_source: pp->setSource(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destination: pp->setDestination(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_hopecount: pp->setHopecount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_hosts: pp->setHosts(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_nodedata: pp->setNodedata(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_sndata: pp->setSndata(value.stringValue()); break;
        case FIELD_type: pp->setType(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MyMessage'", field);
    }
}

const char *MyMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr MyMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    MyMessage *pp = omnetpp::fromAnyPtr<MyMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void MyMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    MyMessage *pp = omnetpp::fromAnyPtr<MyMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'MyMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

