#ifndef GR_JSON_UTIL_H
#define GR_JSON_UTIL_H

#include <string>
#include <base/logging.h>

#if 1
#include <rapidjson.h>
#endif
#if 0
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filestream.h"
#endif

namespace gr {

inline bool json_is_string(const rapidjson::Value &node, const char *name) {
    return (!node.IsNull() && 
            node.IsObject() && 
            node.HasMember(name) && 
            !node[name].IsNull() &&
            node[name].IsString());
}

inline bool json_is_int32(const rapidjson::Value &node, const char *name) {
    return (!node.IsNull() && 
            node.IsObject() && 
            node.HasMember(name) && 
            !node[name].IsNull() &&
            node[name].IsInt());
}

inline bool json_is_int64(const rapidjson::Value &node, const char *name) {
    return (!node.IsNull() && 
            node.IsObject() && 
            node.HasMember(name) && 
            !node[name].IsNull() &&
            node[name].IsInt64());
}

inline bool json_is_uint32(const rapidjson::Value &node, const char *name) {
    return (!node.IsNull() && 
            node.IsObject() && 
            node.HasMember(name) && 
            !node[name].IsNull() &&
            node[name].IsUint());
}

inline bool json_is_uint64(const rapidjson::Value &node, const char *name) {
    return (!node.IsNull() && 
            node.IsObject() && 
            node.HasMember(name) && 
            !node[name].IsNull() &&
            node[name].IsUint64());
}

inline bool json_is_double(const rapidjson::Value &node, const char *name) {
    return (!node.IsNull() && 
            node.IsObject() && 
            node.HasMember(name) && 
            !node[name].IsNull() &&
            node[name].IsDouble());
}

inline bool json_is_bool(const rapidjson::Value &node, const char *name) {
    return (!node.IsNull() && 
            node.IsObject() && 
            node.HasMember(name) && 
            !node[name].IsNull() &&
            node[name].IsBool());
}

inline bool json_is_array(const rapidjson::Value &node, const char *name) {
    return (!node.IsNull() && 
            node.IsObject() && 
            node.HasMember(name) && 
            !node[name].IsNull() &&
            node[name].IsArray());
}

inline bool json_is_object(const rapidjson::Value &node, const char *name) {
    return (!node.IsNull() && 
            node.IsObject() && 
            node.HasMember(name) && 
            !node[name].IsNull() &&
            node[name].IsObject());
}

/* rapidjson通过数组管理元素,AddMember不会判重，
 * 因此需要先Remove 避免Json中出现相同key。
 * 但Remove内会调用FindMember，Find的实现是数组遍历key比对 效率低
 * 
 * json_overwrite 函数用于覆盖json中kv
 */
template <class T>
inline void json_overwrite(rapidjson::Document *doc, rapidjson::Value *node, \
    const char* key, T value) {
    node->RemoveMember(key);
    rapidjson::Value item(value);
    rapidjson::Value name(key, doc->GetAllocator());
    node->AddMember(name, item, doc->GetAllocator());
}
inline void json_overwrite(rapidjson::Document *doc, rapidjson::Value *node, \
    const char* key, const char* value) {
    node->RemoveMember(key);
    rapidjson::Value item;
    item.SetString(value, doc->GetAllocator());
    rapidjson::Value name(key, doc->GetAllocator());
    node->AddMember(name, item, doc->GetAllocator());
}
inline void json_overwrite(rapidjson::Document *doc, rapidjson::Value *node,
    const char* key, const std::string& value) {
    node->RemoveMember(key);
    rapidjson::Value item;
    item.SetString(value.c_str(), value.size(), doc->GetAllocator());
    rapidjson::Value name(key, doc->GetAllocator());
    node->AddMember(name, item, doc->GetAllocator());
}
inline void json_overwrite(rapidjson::Document *doc, rapidjson::Value *node, 
    const char *key, const rapidjson::Value &value) {
    node->RemoveMember(key);
    rapidjson::Value name(key, doc->GetAllocator());
    rapidjson::Value v(value, doc->GetAllocator());
    node->AddMember(name, v, doc->GetAllocator());
}

/*json set, 
 *不论是否存在，都添加一对kv, 
 *若key已存在，则可能导致最终出现多个相同key的情况
 */
inline void json_set(rapidjson::Document *doc, rapidjson::Value *node, const char *key, int value) {
    assert(doc != nullptr);
    assert(node != nullptr);
    assert(key != nullptr);
    rapidjson::Value name(key, doc->GetAllocator());
    rapidjson::Value item;
    item.SetInt(value);
    node->AddMember(name, item, doc->GetAllocator());
}

inline void json_set(rapidjson::Document *doc, rapidjson::Value *node, const char *key, double value) {
    assert(doc != nullptr);
    assert(node != nullptr);
    assert(key != nullptr);
    rapidjson::Value name(key, doc->GetAllocator());
    rapidjson::Value item;
    item.SetDouble(value);
    node->AddMember(name, item, doc->GetAllocator());
}

inline void json_set(rapidjson::Document *doc, rapidjson::Value *node, const char *key, unsigned int value) {
    assert(doc != nullptr);
    assert(node != nullptr);
    assert(key != nullptr);
    rapidjson::Value name(key, doc->GetAllocator());
    rapidjson::Value item;
    item.SetUint(value);
    node->AddMember(name, item, doc->GetAllocator());
}

inline void json_set(rapidjson::Document *doc, rapidjson::Value *node, const char *key, int64_t value) {
    assert(doc != nullptr);
    assert(node != nullptr);
    assert(key != nullptr);
    rapidjson::Value name(key, doc->GetAllocator());
    rapidjson::Value item;
    item.SetInt64(value);
    node->AddMember(name, item, doc->GetAllocator());
}

inline void json_set(rapidjson::Document *doc, rapidjson::Value *node, const char *key, uint64_t value) {
    assert(doc != nullptr);
    assert(node != nullptr);
    assert(key != nullptr);
    rapidjson::Value name(key, doc->GetAllocator());
    rapidjson::Value item;
    item.SetUint64(value);
    node->AddMember(name, item, doc->GetAllocator());
}

inline void json_set(rapidjson::Document *doc, rapidjson::Value *node, const char *key, bool value) {
    assert(doc != nullptr);
    assert(node != nullptr);
    assert(key != nullptr);
    rapidjson::Value name(key, doc->GetAllocator());
    rapidjson::Value item;
    item.SetBool(value);
    node->AddMember(name, item, doc->GetAllocator());
}

inline void json_set(rapidjson::Document *doc, rapidjson::Value *node, const char *key, const std::string &value) {
    assert(doc != nullptr);
    assert(node != nullptr);
    assert(key != nullptr);
    rapidjson::Value name(key, doc->GetAllocator());
    rapidjson::Value item;
    item.SetString(value.c_str(), value.length(), doc->GetAllocator());
    node->AddMember(name, item, doc->GetAllocator());
}

inline void json_set(rapidjson::Document *doc, rapidjson::Value *node, const char *key, const char *value) {
    assert(doc != nullptr);
    assert(node != nullptr);
    assert(key != nullptr);
    rapidjson::Value name(key, doc->GetAllocator());
    rapidjson::Value item;
    item.SetString(value, doc->GetAllocator());
    node->AddMember(name, item, doc->GetAllocator());
}

inline void json_set(rapidjson::Document *doc, rapidjson::Value *node, const char *key, const rapidjson::Value &value) {
    assert(doc != nullptr);
    assert(node != nullptr);
    assert(key != nullptr);
    rapidjson::Value name(key, doc->GetAllocator());
    rapidjson::Value v(value, doc->GetAllocator());
    node->AddMember(name, v, doc->GetAllocator());
}

inline void json_set(rapidjson::Document *doc, 
        rapidjson::Value *node, const rapidjson::Value &value) {
    assert(doc != nullptr);
    assert(node != nullptr);
    rapidjson::Value v(value, doc->GetAllocator());
    node->PushBack(v, doc->GetAllocator());
}

inline void json_set(rapidjson::Document *doc, rapidjson::Value *node, const std::string &value) {
    assert(doc != nullptr);
    assert(node != nullptr);
    rapidjson::Value item;
    item.SetString(value.c_str(), value.length(), doc->GetAllocator());
    node->PushBack(item, doc->GetAllocator());
}

inline void json_set(rapidjson::Document *doc, rapidjson::Value *node, int64_t value) {
    assert(doc != nullptr);
    assert(node != nullptr);
    rapidjson::Value item;
    item.SetInt64(value);
    node->PushBack(item, doc->GetAllocator());
}

inline void json_set(rapidjson::Document *doc, rapidjson::Value *node, int value) {
    assert(doc != nullptr);
    assert(node != nullptr);
    rapidjson::Value item;
    item.SetInt(value);
    node->PushBack(item, doc->GetAllocator());
}

#if 0
inline void json_set(rapidjson::Document *doc, rapidjson::Value *node, const char *key, const rapidjson::Document &value) {
    assert(doc != nullptr);
    assert(key != nullptr);
    rapidjson::Value name(key, doc->GetAllocator());
    node->AddMember(name, value, doc->GetAllocator());
}
#endif

// writer
inline void json_write(const rapidjson::Value &value, std::string *out) {
    assert(out != nullptr);
    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    value.Accept(writer);
    *out = s.GetString(); 
}

inline void json_write(const rapidjson::Value &value, rapidjson::StringBuffer *s) {
    assert(s != nullptr);
    rapidjson::Writer<rapidjson::StringBuffer> writer(*s);
    value.Accept(writer);
}

inline void json_write(const rapidjson::Document &doc, rapidjson::StringBuffer *s) {
    assert(s != nullptr);
    rapidjson::Writer<rapidjson::StringBuffer> writer(*s);
    doc.Accept(writer);
}
}

#endif  // GR_JSON_UTIL_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
