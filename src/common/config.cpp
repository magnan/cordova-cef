/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
*/

#include "config.h"

Config::Config(const std::wstring configXMLFile)
  : INIT_LOGGER(Config)
{
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(configXMLFile.c_str());
  if(result.status == pugi::status_ok)
  {
    // get name node
    pugi::xpath_node name_node =  doc.select_single_node(L"/widget/name");
    _appName = name_node.node().text().get();
    pugi::xpath_node content_node =  doc.select_single_node(L"/widget/content");
    _startDocument = content_node.node().attribute(L"src").value();
  }
  else
  {
    BOOST_LOG_SEV(logger(), error) << "failed to parse config xml '" << configXMLFile << "' result=" << result.status;
    //TODO: error handling
  }
}

Config::~Config()
{

}


