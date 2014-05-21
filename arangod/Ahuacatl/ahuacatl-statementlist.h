////////////////////////////////////////////////////////////////////////////////
/// @brief Ahuacatl, statement list
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2013 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Jan Steemann
/// @author Copyright 2012-2013, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_AHUACATL_AHUACATL_STATEMENTLIST_H
#define TRIAGENS_AHUACATL_AHUACATL_STATEMENTLIST_H 1

#include "BasicsC/common.h"
#include "BasicsC/vector.h"

struct TRI_aql_node_s;

// -----------------------------------------------------------------------------
// --SECTION--                                                      public types
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Ahuacatl
/// @{
////////////////////////////////////////////////////////////////////////////////

typedef struct TRI_aql_statement_list_s {
  TRI_vector_pointer_t _statements;
  size_t _currentLevel;
}
TRI_aql_statement_list_t;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                        constructors / destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Ahuacatl
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief init the global nodes at program start
////////////////////////////////////////////////////////////////////////////////

void TRI_GlobalInitStatementListAql (void);

////////////////////////////////////////////////////////////////////////////////
/// @brief de-init the global nodes at program end
////////////////////////////////////////////////////////////////////////////////

void TRI_GlobalFreeStatementListAql (void);

////////////////////////////////////////////////////////////////////////////////
/// @brief create and initialize a statement list
////////////////////////////////////////////////////////////////////////////////

TRI_aql_statement_list_t* TRI_CreateStatementListAql (void);

////////////////////////////////////////////////////////////////////////////////
/// @brief free a statement list
////////////////////////////////////////////////////////////////////////////////

void TRI_FreeStatementListAql (TRI_aql_statement_list_t* const);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                  public functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Ahuacatl
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief get the address of the dummy non-op node
////////////////////////////////////////////////////////////////////////////////

struct TRI_aql_node_s* TRI_GetDummyNopNodeAql (void);

////////////////////////////////////////////////////////////////////////////////
/// @brief pull out subqueries in the statement list from the middle to the
/// beginning
////////////////////////////////////////////////////////////////////////////////

void TRI_PulloutStatementListAql (TRI_aql_statement_list_t* const);

////////////////////////////////////////////////////////////////////////////////
/// @brief remove all non-ops from the statement list
///
/// this is achieved by skipping over all nop nodes in the statement list
/// the resulting statement list will contain the remaining nodes only
////////////////////////////////////////////////////////////////////////////////

void TRI_CompactStatementListAql (TRI_aql_statement_list_t* const);

////////////////////////////////////////////////////////////////////////////////
/// @brief insert a statement into the statement list
////////////////////////////////////////////////////////////////////////////////

bool TRI_InsertStatementListAql (TRI_aql_statement_list_t* const,
                                 struct TRI_aql_node_s* const,
                                 const size_t);

////////////////////////////////////////////////////////////////////////////////
/// @brief add a statement to the end of the statement list
////////////////////////////////////////////////////////////////////////////////

bool TRI_AppendStatementListAql (TRI_aql_statement_list_t* const,
                                 struct TRI_aql_node_s* const);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|/// @page\\|// --SECTION--\\|/// @\\}"
// End:
