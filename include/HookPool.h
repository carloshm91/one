/* -------------------------------------------------------------------------- */
/* Copyright 2002-2019, OpenNebula Project, OpenNebula Systems                */
/*                                                                            */
/* Licensed under the Apache License, Version 2.0 (the "License"); you may    */
/* not use this file except in compliance with the License. You may obtain    */
/* a copy of the License at                                                   */
/*                                                                            */
/* http://www.apache.org/licenses/LICENSE-2.0                                 */
/*                                                                            */
/* Unless required by applicable law or agreed to in writing, software        */
/* distributed under the License is distributed on an "AS IS" BASIS,          */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   */
/* See the License for the specific language governing permissions and        */
/* limitations under the License.                                             */
/* -------------------------------------------------------------------------- */

#ifndef HOOK_POOL_H_
#define HOOK_POOL_H_

#include "PoolSQL.h"
#include "Hook.h"

using namespace std;

class HookPool : public PoolSQL
{
public:
    HostPool(SqlDB * db) : PoolSQL(db, Hook::table);

    ~HostPool(){};

    /**
     *  Function to allocate a new Hook object
     *    @param oid the id assigned to the Hook
     *    @return the oid assigned to the object or -1 in case of failure
     */
    int allocate (
        int *  oid,
        const string& name,
        const string& cmd,
        const string& args,
        HookType  _ht,
        PoolObjectSQL::ObjectType  _rt,
        bool remote);

    /**
     *  Function to get a Hook from the pool, if the object is not in memory
     *  it is loaded from the DB
     *    @param oid Hook unique id
     *    @return a pointer to the Hook, 0 if the Hook could not be loaded
     */
    Hook * get(int oid)
    {
        return static_cast<Hook *>(PoolSQL::get(oid));
    };

    /**
     *  Function to get a read only Hook from the pool, if the object is not in memory
     *  it is loaded from the DB
     *    @param oid Hook unique id
     *    @return a pointer to the Hook, 0 if the Host could not be loaded
     */
    Hook * get_ro(int oid)
    {
        return static_cast<Hook *>(PoolSQL::get_ro(oid));
    }

    /**
     *  Function to get a Hook from the pool, if the object is not in memory
     *  it is loaded from the DB
     *    @param oid Hook unique id
     *    @return a pointer to the Hook, 0 if the Hook could not be loaded
     */
    Hook * get(string name)
    {
        return static_cast<Hook *>(PoolSQL::get(name, -1));
    };

    /**
     *  Function to get a read only Hook from the pool, if the object is not in memory
     *  it is loaded from the DB
     *    @param oid Hook unique id
     *    @return a pointer to the Hook, 0 if the Host could not be loaded
     */
    Hook * get_ro(string name)
    {
        return static_cast<Hook *>(PoolSQL::get_ro(name, -1));
    }

    /**
     *  Bootstraps the database table(s) associated to the Hook pool
     *    @return 0 on success
     */
    static int bootstrap(SqlDB *_db)
    {
        return Host::bootstrap(_db);
    };

    /**
     *  Dumps the HOOK pool in XML format. A filter can be also added to the
     *  query
     *  @param oss the output stream to dump the pool contents
     *  @param where filter for the objects, defaults to all
     *  @param limit parameters used for pagination
     *  @param desc descending order of pool elements
     *
     *  @return 0 on success
     */
    int dump(string& oss, const string& where, const string& limit,
        bool desc)
    {
        return PoolSQL::dump(oss, "HOOK_POOL", "body", Host::table, where, limit, desc);
    };
}