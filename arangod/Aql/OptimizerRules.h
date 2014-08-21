////////////////////////////////////////////////////////////////////////////////
/// @brief rules for the query optimizer
///
/// @file arangod/Aql/OptimizerRules.h
///
/// DISCLAIMER
///
/// Copyright 2010-2014 triagens GmbH, Cologne, Germany
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
/// @author Max Neunhoeffer
/// @author Copyright 2014, triagens GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGOD_AQL_OPTIMIZER_RULES_H
#define ARANGOD_AQL_OPTIMIZER_RULES 1

#include <Basics/Common.h>

#include "Aql/Optimizer.h"
#include "Aql/Indexes.h"

namespace triagens {
  namespace aql {

// -----------------------------------------------------------------------------
// --SECTION--                                           rules for the optimizer
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @brief remove a CalculationNode that is never needed
////////////////////////////////////////////////////////////////////////////////

    int removeUnnecessaryFiltersRule (Optimizer*, ExecutionPlan*, Optimizer::PlanList&, bool&);

////////////////////////////////////////////////////////////////////////////////
/// @brief move calculations up in the plan
////////////////////////////////////////////////////////////////////////////////

    int moveCalculationsUpRule (Optimizer*, ExecutionPlan*, Optimizer::PlanList&, bool&);

////////////////////////////////////////////////////////////////////////////////
/// @brief remove a CalculationNode that is never needed
////////////////////////////////////////////////////////////////////////////////

    int removeUnnecessaryCalculationsRule (Optimizer*, ExecutionPlan*, Optimizer::PlanList&, bool&);

////////////////////////////////////////////////////////////////////////////////
/// @brief remove a CalculationNode that is never needed
////////////////////////////////////////////////////////////////////////////////

    int useIndexRange (Optimizer*, ExecutionPlan*, Optimizer::PlanList&, bool&);

  }  // namespace aql
}  // namespace triagens

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "^\\(/// @brief\\|/// {@inheritDoc}\\|/// @addtogroup\\|// --SECTION--\\|/// @\\}\\)"
// End:
