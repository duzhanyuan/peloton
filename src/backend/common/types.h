//===----------------------------------------------------------------------===//
//
//                         PelotonDB
//
// types.h
//
// Identification: src/backend/common/types.h
//
// Copyright (c) 2015, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <string>
#include <cstdint>
#include <climits>
#include <limits>
#include <cassert>

namespace peloton {

//===--------------------------------------------------------------------===//
// NULL-related Constants
//===--------------------------------------------------------------------===//

/// NULL
#define INT8_NULL INT8_MIN
#define INT16_NULL INT16_MIN
#define INT32_NULL INT32_MIN
#define INT64_NULL INT64_MIN

/// Minimum value user can represent that is not NULL
#define PELOTON_INT8_MIN INT8_NULL + 1
#define PELOTON_INT16_MIN INT16_NULL + 1
#define PELOTON_INT32_MIN INT32_NULL + 1
#define PELOTON_INT64_MIN INT64_NULL + 1
#define DECIMAL_MIN -9999999
#define DECIMAL_MAX 9999999

/// Float/Double less than these values are NULL
#define FLOAT_NULL -3.4e+38f
#define DOUBLE_NULL -1.7E+308

// Values to be substituted as NULL
#define FLOAT_MIN -3.40282347e+38f
#define DOUBLE_MIN -1.7976931348623157E+308

// Objects (i.e., VARCHAR) with length prefix of -1 are NULL
#define OBJECTLENGTH_NULL -1
#define VALUE_COMPARE_LESSTHAN -1
#define VALUE_COMPARE_EQUAL 0
#define VALUE_COMPARE_GREATERTHAN 1

#define DEFAULT_DB_ID 12345
#define DEFAULT_DB_NAME "default"

#define DEFAULT_TUPLES_PER_TILEGROUP 1000

//===--------------------------------------------------------------------===//
// Other Constants
//===--------------------------------------------------------------------===//

#define VARCHAR_LENGTH_SHORT 16
#define VARCHAR_LENGTH_MID 256
#define VARCHAR_LENGTH_LONG 4096

//===--------------------------------------------------------------------===//
// Port to OSX
//===---------------------------
#ifdef __APPLE__
#define off64_t off_t
#define MAP_ANONYMOUS MAP_ANON
#endif

//===--------------------------------------------------------------------===//
// Value types
// This file defines all the types that we will support
// We do not allow for user-defined types, nor do we try to do anything dynamic.
//===--------------------------------------------------------------------===//

enum PostgresValueType {
  POSTGRES_VALUE_TYPE_BOOLEAN = 16,

  POSTGRES_VALUE_TYPE_SMALLINT = 21,
  POSTGRES_VALUE_TYPE_INTEGER = 23,
  POSTGRES_VALUE_TYPE_BIGINT = 20,

  POSTGRES_VALUE_TYPE_DOUBLE = 701,

  POSTGRES_VALUE_TYPE_TEXT = 25,

  POSTGRES_VALUE_TYPE_BPCHAR = 1042,
  POSTGRES_VALUE_TYPE_BPCHAR2 = 1014,

  POSTGRES_VALUE_TYPE_VARCHAR = 1015,
  POSTGRES_VALUE_TYPE_VARCHAR2 = 1043,

  POSTGRES_VALUE_TYPE_TIMESTAMPS = 1114,
  POSTGRES_VALUE_TYPE_TIMESTAMPS2 = 1184,

  POSTGRES_VALUE_TYPE_DECIMAL = 1700

};

enum ValueType {
  VALUE_TYPE_INVALID = 0,  // invalid value type
  VALUE_TYPE_NULL = 1,     // NULL type

  VALUE_TYPE_TINYINT = 3,     // 1 byte integer
  VALUE_TYPE_SMALLINT = 4,    // 2 bytes integer
  VALUE_TYPE_INTEGER = 5,     // 4 bytes integer
  VALUE_TYPE_BIGINT = 6,      // 8 bytes integer
  VALUE_TYPE_DOUBLE = 8,      // 8 bytes floating number
  VALUE_TYPE_VARCHAR = 9,     // variable length chars
  VALUE_TYPE_TIMESTAMP = 11,  // 8 bytes integer
  VALUE_TYPE_DECIMAL = 22,    // decimal(p,s)
  VALUE_TYPE_BOOLEAN = 23,
  VALUE_TYPE_ADDRESS = 24,
  VALUE_TYPE_VARBINARY = 25,  // variable length bytes
};

//===--------------------------------------------------------------------===//
// Predicate Expression Operation Types
//===--------------------------------------------------------------------===//

enum ExpressionType {
  EXPRESSION_TYPE_INVALID = 0,

  //===--------------------------------------------------------------------===//
  // Arithmetic Operators
  //===--------------------------------------------------------------------===//

  EXPRESSION_TYPE_OPERATOR_PLUS =
      1,  // left + right (both must be number. implicitly casted)
  EXPRESSION_TYPE_OPERATOR_MINUS =
      2,  // left - right (both must be number. implicitly casted)
  EXPRESSION_TYPE_OPERATOR_MULTIPLY =
      3,  // left * right (both must be number. implicitly casted)
  EXPRESSION_TYPE_OPERATOR_DIVIDE =
      4,  // left / right (both must be number. implicitly casted)
  EXPRESSION_TYPE_OPERATOR_CONCAT =
      5,  // left || right (both must be char/varchar)
  EXPRESSION_TYPE_OPERATOR_MOD = 6,  // left % right (both must be integer)
  EXPRESSION_TYPE_OPERATOR_CAST =
      7,  // explicitly cast left as right (right is integer in ValueType enum)
  EXPRESSION_TYPE_OPERATOR_NOT = 8,          // logical not operator
  EXPRESSION_TYPE_OPERATOR_UNARY_MINUS = 9,  // unary minus operator

  //===--------------------------------------------------------------------===//
  // Comparison Operators
  //===--------------------------------------------------------------------===//

  EXPRESSION_TYPE_COMPARE_EQ = 10,  // equal operator between left and right
  EXPRESSION_TYPE_COMPARE_NE = 11,  // inequal operator between left and right
  EXPRESSION_TYPE_COMPARE_LT = 12,  // less than operator between left and right
  EXPRESSION_TYPE_COMPARE_GT =
      13,  // greater than operator between left and right
  EXPRESSION_TYPE_COMPARE_LTE =
      14,  // less than equal operator between left and right
  EXPRESSION_TYPE_COMPARE_GTE =
      15,  // greater than equal operator between left and right
  EXPRESSION_TYPE_COMPARE_LIKE =
      16,  // LIKE operator (left LIKE right). both children must be string.

  //===--------------------------------------------------------------------===//
  // Conjunction Operators
  //===--------------------------------------------------------------------===//

  EXPRESSION_TYPE_CONJUNCTION_AND = 20,
  EXPRESSION_TYPE_CONJUNCTION_OR = 21,

  //===--------------------------------------------------------------------===//
  // Values
  //===--------------------------------------------------------------------===//

  EXPRESSION_TYPE_VALUE_CONSTANT = 30,
  EXPRESSION_TYPE_VALUE_PARAMETER = 31,
  EXPRESSION_TYPE_VALUE_TUPLE = 32,
  EXPRESSION_TYPE_VALUE_TUPLE_ADDRESS = 33,
  EXPRESSION_TYPE_VALUE_NULL = 34,

  //===--------------------------------------------------------------------===//
  // Aggregates
  //===--------------------------------------------------------------------===//

  EXPRESSION_TYPE_AGGREGATE_COUNT = 40,
  EXPRESSION_TYPE_AGGREGATE_COUNT_STAR = 41,
  EXPRESSION_TYPE_AGGREGATE_SUM = 42,
  EXPRESSION_TYPE_AGGREGATE_MIN = 43,
  EXPRESSION_TYPE_AGGREGATE_MAX = 44,
  EXPRESSION_TYPE_AGGREGATE_AVG = 45,
  EXPRESSION_TYPE_AGGREGATE_WEIGHTED_AVG = 46,

  //===--------------------------------------------------------------------===//
  // Parser
  //===--------------------------------------------------------------------===//

  EXPRESSION_TYPE_STAR = 50,
  EXPRESSION_TYPE_PLACEHOLDER = 51,
  EXPRESSION_TYPE_COLUMN_REF = 52,
  EXPRESSION_TYPE_FUNCTION_REF = 53,

  //===--------------------------------------------------------------------===//
  // Misc
  //===--------------------------------------------------------------------===//
  EXPRESSION_TYPE_CAST = 60
};

//===--------------------------------------------------------------------===//
// Storage Backend Types
//===--------------------------------------------------------------------===//

enum BackendType {
  BACKEND_TYPE_INVALID = 0,  // invalid backend type

  BACKEND_TYPE_VM = 1,  // on volatile memory
  BACKEND_TYPE_NVM = 2  // on non-volatile memory
};

//===--------------------------------------------------------------------===//
// Index Types
//===--------------------------------------------------------------------===//

enum IndexType {
  INDEX_TYPE_INVALID = 0,  // invalid index type

  INDEX_TYPE_BTREE = 1  // btree
};

enum IndexConstraintType {
  INDEX_CONSTRAINT_TYPE_INVALID = 0,  // invalid index constraint type

  INDEX_CONSTRAINT_TYPE_DEFAULT =
      1,  // default type - not used to enforce constraints
  INDEX_CONSTRAINT_TYPE_PRIMARY_KEY =
      2,                            // used to enforce primary key constraint
  INDEX_CONSTRAINT_TYPE_UNIQUE = 3  // used for unique constraint
};

//===--------------------------------------------------------------------===//
// Plan Node Types
//===--------------------------------------------------------------------===//

enum PlanNodeType {
  PLAN_NODE_TYPE_INVALID = 0,  // invalid plan node type

  // Scan Nodes
  PLAN_NODE_TYPE_ABSTRACT_SCAN = 10,
  PLAN_NODE_TYPE_SEQSCAN = 11,
  PLAN_NODE_TYPE_INDEXSCAN = 12,

  // Join Nodes
  PLAN_NODE_TYPE_NESTLOOP = 20,
  PLAN_NODE_TYPE_NESTLOOPINDEX = 21,
  PLAN_NODE_TYPE_MERGEJOIN = 22,

  // Mutator Nodes
  PLAN_NODE_TYPE_UPDATE = 30,
  PLAN_NODE_TYPE_INSERT = 31,
  PLAN_NODE_TYPE_DELETE = 32,

  // Communication Nodes
  PLAN_NODE_TYPE_SEND = 40,
  PLAN_NODE_TYPE_RECEIVE = 41,
  PLAN_NODE_TYPE_PRINT = 42,

  // Algebra Nodes
  PLAN_NODE_TYPE_AGGREGATE = 50,
  PLAN_NODE_TYPE_HASHAGGREGATE = 51,  // TODO: Remove it.
  PLAN_NODE_TYPE_UNION = 52,
  PLAN_NODE_TYPE_ORDERBY = 53,
  PLAN_NODE_TYPE_PROJECTION = 54,
  PLAN_NODE_TYPE_MATERIALIZE = 55,
  PLAN_NODE_TYPE_LIMIT = 56,
  PLAN_NODE_TYPE_DISTINCT = 57,
  PLAN_NODE_TYPE_SETOP = 58,   // set operation
  PLAN_NODE_TYPE_APPEND = 59,  // append

  PLAN_NODE_TYPE_AGGREGATE_V2 = 61,

  // Utility
  PLAN_NODE_TYPE_RESULT = 70
};

//===--------------------------------------------------------------------===//
// Create Types
//===--------------------------------------------------------------------===//

enum CreateType {
  CREATE_TYPE_INVALID = 0,  // invalid create type

  CREATE_TYPE_DB = 1,         // db create type
  CREATE_TYPE_TABLE = 2,      // table create type
  CREATE_TYPE_INDEX = 3,      // index create type
  CREATE_TYPE_CONSTRAINT = 4  // constraint create type

};

//===--------------------------------------------------------------------===//
// Statement Types
//===--------------------------------------------------------------------===//

enum StatementType {
  STATEMENT_TYPE_INVALID = 0,  // invalid statement type

  STATEMENT_TYPE_SELECT = 1,        // select statement type
  STATEMENT_TYPE_INSERT = 3,        // insert statement type
  STATEMENT_TYPE_UPDATE = 4,        // update statement type
  STATEMENT_TYPE_DELETE = 5,        // delete statement type
  STATEMENT_TYPE_CREATE = 6,        // create statement type
  STATEMENT_TYPE_DROP = 7,          // drop statement type
  STATEMENT_TYPE_PREPARE = 8,       // prepare statement type
  STATEMENT_TYPE_EXECUTE = 9,       // execute statement type
  STATEMENT_TYPE_EXPORT = 10,       // export statement type
  STATEMENT_TYPE_RENAME = 11,       // rename statement type
  STATEMENT_TYPE_ALTER = 12,        // alter statement type
  STATEMENT_TYPE_TRANSACTION = 13,  // transaction statement type
};

//===--------------------------------------------------------------------===//
// Join Types
//===--------------------------------------------------------------------===//

enum PelotonJoinType {
  JOIN_TYPE_INVALID = 0,  // invalid join type

  JOIN_TYPE_LEFT = 1,   // left
  JOIN_TYPE_RIGHT = 2,  // right
  JOIN_TYPE_INNER = 3,  // inner
  JOIN_TYPE_OUTER = 4   // outer
};

//===--------------------------------------------------------------------===//
// Aggregate Types
//===--------------------------------------------------------------------===//
enum PelotonAggregateType {
  AGGREGATE_TYPE_INVALID = 0,
  AGGREGATE_TYPE_SORTED = 1,
  AGGREGATE_TYPE_HASH = 2,
  AGGREGATE_TYPE_PLAIN = 3  // no group-by
};

//===--------------------------------------------------------------------===//
// Table Reference Types
//===--------------------------------------------------------------------===//

enum TableReferenceType {
  TABLE_REFERENCE_TYPE_INVALID = 0,  // invalid table reference type

  TABLE_REFERENCE_TYPE_NAME = 1,          // table name
  TABLE_REFERENCE_TYPE_SELECT = 2,        // output of select
  TABLE_REFERENCE_TYPE_JOIN = 3,          // output of join
  TABLE_REFERENCE_TYPE_CROSS_PRODUCT = 4  // out of cartesian product
};

//===--------------------------------------------------------------------===//
// Insert Types
//===--------------------------------------------------------------------===//

enum InsertType {
  INSERT_TYPE_INVALID = 0,  // invalid insert type

  INSERT_TYPE_VALUES = 1,  // values
  INSERT_TYPE_SELECT = 2   // select
};

//===--------------------------------------------------------------------===//
// Payload Types
//===--------------------------------------------------------------------===//

enum PayloadType {
  PAYLOAD_TYPE_INVALID = 0,  // invalid message type

  PAYLOAD_TYPE_CLIENT_REQUEST = 1,   // request
  PAYLOAD_TYPE_CLIENT_RESPONSE = 2,  // response
  PAYLOAD_TYPE_STOP = 3              // stop loop
};

//===--------------------------------------------------------------------===//
// Task Priority Types
//===--------------------------------------------------------------------===//

enum TaskPriorityType {
  TASK_PRIORTY_TYPE_INVALID = 0,  // invalid priority

  TASK_PRIORTY_TYPE_LOW = 10,
  TASK_PRIORTY_TYPE_NORMAL = 11,
  TASK_PRIORTY_TYPE_HIGH = 12
};

//===--------------------------------------------------------------------===//
// Result Types
//===--------------------------------------------------------------------===//

enum Result {
  RESULT_INVALID = 0,  // invalid result type

  RESULT_SUCCESS = 1,
  RESULT_FAILURE = 2,
  RESULT_ABORTED = 3,  // aborted
  RESULT_NOOP = 4,     // no op
  RESULT_UNKNOWN = 5
};

//===--------------------------------------------------------------------===//
// Constraint Types
//===--------------------------------------------------------------------===//

enum PostgresConstraintType {
  POSTGRES_CONSTRAINT_NULL, /* not standard SQL, but a lot of people * expect it
                               */

  POSTGRES_CONSTRAINT_NOTNULL,
  POSTGRES_CONSTRAINT_DEFAULT,
  POSTGRES_CONSTRAINT_CHECK,
  POSTGRES_CONSTRAINT_PRIMARY,
  POSTGRES_CONSTRAINT_UNIQUE,
  POSTGRES_CONSTRAINT_EXCLUSION,
  POSTGRES_CONSTRAINT_FOREIGN,
  POSTGRES_CONSTRAINT_ATTR_DEFERRABLE, /* attributes for previous constraint
                                          node */
  POSTGRES_CONSTRAINT_ATTR_NOT_DEFERRABLE,
  POSTGRES_CONSTRAINT_ATTR_DEFERRED,
  POSTGRES_CONSTRAINT_ATTR_IMMEDIATE
};

enum ConstraintType {
  CONSTRAINT_TYPE_INVALID = 0,  // invalid

  CONSTRAINT_TYPE_NULL = 1,      // notnull
  CONSTRAINT_TYPE_NOTNULL = 2,   // notnull
  CONSTRAINT_TYPE_DEFAULT = 3,   // default
  CONSTRAINT_TYPE_CHECK = 4,     // check
  CONSTRAINT_TYPE_PRIMARY = 5,   // primary key
  CONSTRAINT_TYPE_UNIQUE = 6,    // unique
  CONSTRAINT_TYPE_FOREIGN = 7,   // foreign key
  CONSTRAINT_TYPE_EXCLUSION = 8  // foreign key
};

//===--------------------------------------------------------------------===//
// Set Operation Types
//===--------------------------------------------------------------------===//
enum SetOpType {
  SETOP_TYPE_INVALID = 0,

  SETOP_TYPE_INTERSECT = 1,
  SETOP_TYPE_INTERSECT_ALL = 2,
  SETOP_TYPE_EXCEPT = 3,
  SETOP_TYPE_EXCEPT_ALL = 4
};

//===--------------------------------------------------------------------===//
// Type definitions.
//===--------------------------------------------------------------------===//

typedef uint16_t oid_t;

static const oid_t START_OID = 0;

static const oid_t INVALID_OID = std::numeric_limits<oid_t>::max();

static const oid_t MAX_OID = std::numeric_limits<oid_t>::max() - 1;

// For transaction id

typedef uint64_t txn_id_t;

static const txn_id_t INVALID_TXN_ID = 0;

static const txn_id_t START_TXN_ID = 1;

static const txn_id_t MAX_TXN_ID = std::numeric_limits<txn_id_t>::max();

// For commit id

typedef uint64_t cid_t;

static const cid_t INVALID_CID = 0;

static const cid_t START_CID = 1;

static const cid_t MAX_CID = std::numeric_limits<cid_t>::max();

//===--------------------------------------------------------------------===//
// ItemPointer
//===--------------------------------------------------------------------===//

// logical physical location
struct ItemPointer {
  // block
  oid_t block;

  // 0-based offset within block
  oid_t offset;

  ItemPointer() : block(INVALID_OID), offset(INVALID_OID) {}

  ItemPointer(oid_t block, oid_t offset) : block(block), offset(offset) {}
};

extern ItemPointer INVALID_ITEMPOINTER;

//===--------------------------------------------------------------------===//
// Utilities
//===--------------------------------------------------------------------===//

/// Works only for fixed-length types
std::size_t GetTypeSize(ValueType type);

bool IsNumeric(ValueType type);

bool HexDecodeToBinary(unsigned char *bufferdst, const char *hexString);

//===--------------------------------------------------------------------===//
// Transformers
//===--------------------------------------------------------------------===//

std::string BackendTypeToString(BackendType type);
BackendType StringToBackendType(std::string str);

std::string ValueTypeToString(ValueType type);
ValueType StringToValueType(std::string str);

std::string ExpressionTypeToString(ExpressionType type);
ExpressionType StringToExpressionType(std::string str);

std::string IndexTypeToString(IndexType type);
IndexType StringToIndexType(std::string str);

std::string PlanNodeTypeToString(PlanNodeType type);
PlanNodeType StringToPlanNodeType(std::string str);

std::string ConstraintTypeToString(ConstraintType type);
ConstraintType StringToConstraintType(std::string str);

ValueType PostgresValueTypeToPelotonValueType(
    PostgresValueType PostgresValType);
ConstraintType PostgresConstraintTypeToPelotonConstraintType(
    PostgresConstraintType PostgresConstrType);

//===--------------------------------------------------------------------===//
// Asserts
//===--------------------------------------------------------------------===//

#ifndef NDEBUG

#define AssertMsg(condition, message)                                    \
  do {                                                                   \
    if (!(condition)) {                                                  \
      std::cerr << "Assertion `" #condition "` failed in " << __FILE__   \
                << " line " << __LINE__ << ": " << message << std::endl; \
      std::exit(EXIT_FAILURE);                                           \
    }                                                                    \
  } while (false)

#else

#define AssertMsg(condition, message) \
  do {                                \
  } while (false)

#endif

}  // End peloton namespace
