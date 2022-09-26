// This file is made available under Elastic License 2.0.
// This file is based on code available under the Apache license here:
//   https://github.com/apache/incubator-doris/blob/master/be/src/agent/agent_server.h

// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "gutil/macros.h"

namespace starrocks {

class ExecEnv;
class Status;
class TAgentTaskRequest;
class TAgentResult;
class TAgentPublishRequest;
class TSnapshotRequest;
class ThreadPool;

// Each method corresponds to one RPC from FE Master, see BackendService.
class AgentServer {
public:
    explicit AgentServer(ExecEnv* exec_env);

    ~AgentServer();

    void init_or_die();

    void submit_tasks(TAgentResult& agent_result, const std::vector<TAgentTaskRequest>& tasks);

    void make_snapshot(TAgentResult& agent_result, const TSnapshotRequest& snapshot_request);

    void release_snapshot(TAgentResult& agent_result, const std::string& snapshot_path);

    void publish_cluster_state(TAgentResult& agent_result, const TAgentPublishRequest& request);

    // |type| should be one of `TTaskType::type`, didn't define type as  `TTaskType::type` because
    // I don't want to include the header file `gen_cpp/Types_types.h` here.
    //
    // Returns nullptr if `type` is not a valid value of `TTaskType::type`.
    ThreadPool* get_thread_pool(int type) const;

    DISALLOW_COPY_AND_MOVE(AgentServer);

private:
    class Impl;
    std::unique_ptr<Impl> _impl;
};

} // end namespace starrocks
