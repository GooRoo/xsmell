// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://sam.zoy.org/wtfpl/COPYING for more details.

#ifndef XSMELL_HPP_2145_24062009
#define XSMELL_HPP_2145_24062009

#include <string>
#include <ostream>
#include <map>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/static_assert.hpp>

namespace xsmell
{
    namespace mpl = boost::mpl;

    template<typename Name>
    struct close_tag { };

    template<typename Name>
    struct tag : Name { close_tag<Name> operator! () const { return close_tag<Name>(); } };

    template<typename Tags>
    struct block 
    { 
        block(const std::string &text) : text(text) { } 
        std::string text; 
    };

    namespace { block<mpl::vector<> > _(""); }

    template<typename Tags, typename Name>
    block<typename mpl::push_back<Tags, Name>::type> 
    operator< (const block<Tags> &em, const tag<Name> &t) 
    { 
        std::string ret = em.text + '<' + Name::str(); 
        for (std::map<std::string, std::string>::const_iterator p = t.attribs.begin(), e = t.attribs.end(); p != e; ++p)
            ret += (" " + p->first + "=\"" + p->second + '\"');
        return ret;
    }

    template<typename Tags>
    block<Tags> 
    operator> (const block<Tags> &em, const block<mpl::vector<> > &) { return em.text + '>'; }

    template<typename Tags, typename T>
    block<Tags> 
    operator> (const block<Tags> &em, const T &obj) { return em.text + '>' + boost::lexical_cast<std::string>(obj); }

    template<typename Tags, typename Name>
    block<typename mpl::pop_back<Tags>::type>
    operator< (const block<Tags> &em, close_tag<Name>)
    {
        BOOST_STATIC_ASSERT((boost::is_same<Name, typename mpl::back<Tags>::type>::value));
        return em.text + "</" + Name::str();
    }

    struct document
    {
        template<typename Tags>
        document(const block<Tags> &em) : text(em.text) { BOOST_STATIC_ASSERT(mpl::empty<Tags>::value); }
        std::string text;
    };

    inline std::ostream &operator<< (std::ostream &out, const document &doc) { return out << doc.text; }
}

#define JOIN_IMPL(a,b) a ## b
#define JOIN(a,b) JOIN_IMPL(a,b)

#define ATTRIB(name) \
    JOIN(lalala2_, name) }; \
    \
    template<typename T> \
    tag_type name(const T &obj) const \
    { \
        tag_type ret; \
        ret.attribs = attribs; \
        ret.attribs[#name] = boost::lexical_cast<std::string>(obj); \
        return ret; \
    } \
    \
    enum { JOIN(lalala1_, name)

#define NO_ATTRIBS JOIN(lalala3_, __LINE__)

#define TAG(name, ...) \
    namespace xsmell \
    { \
        namespace tagnames \
        { \
            struct name \
            { \
                typedef tag<name> tag_type; \
                static const char *str() { return #name; } \
                \
                enum { lalala1, \
                __VA_ARGS__ \
                , lalala2 }; \
                \
                std::map<std::string, std::string> attribs; \
            };\
        } \
        namespace { tag<tagnames::name> name; } \
    } \
    enum JOIN(pointless_, __LINE__) {}

#endif // XSMELL_HPP_2145_24062009
