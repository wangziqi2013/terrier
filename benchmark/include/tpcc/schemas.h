#pragma once

#include "catalog/schema.h"
#include "common/macros.h"

namespace terrier::tpcc {

// 1.3.1
struct Schemas {
  Schemas() = delete;

  static catalog::Schema BuildItemSchema(uint64_t *const oid_counter) {
    std::vector<catalog::Schema::Column> item_columns;
    item_columns.reserve(num_item_cols);

    item_columns.emplace_back("I_ID", type::TypeId::INTEGER, false, static_cast<catalog::col_oid_t>(++(*oid_counter)));
    item_columns.emplace_back("I_IM_ID", type::TypeId::INTEGER, false,
                              static_cast<catalog::col_oid_t>(++(*oid_counter)));
    item_columns.emplace_back("I_NAME", type::TypeId::VARCHAR, 24, false,
                              static_cast<catalog::col_oid_t>(++(*oid_counter)));
    item_columns.emplace_back("I_PRICE", type::TypeId::DECIMAL, false,
                              static_cast<catalog::col_oid_t>(++(*oid_counter)));
    item_columns.emplace_back("I_DATA", type::TypeId::VARCHAR, 50, false,
                              static_cast<catalog::col_oid_t>(++(*oid_counter)));

    TERRIER_ASSERT(item_columns.size() == num_item_cols, "Wrong number of columns for Item schema.");

    return catalog::Schema(item_columns);
  }

  static catalog::Schema BuildWarehouseSchema(uint64_t *const oid_counter) {
    std::vector<catalog::Schema::Column> warehouse_columns;
    warehouse_columns.reserve(num_warehouse_cols);

    warehouse_columns.emplace_back("W_ID", type::TypeId::INTEGER, false,
                                   static_cast<catalog::col_oid_t>(++(*oid_counter)));
    warehouse_columns.emplace_back("W_NAME", type::TypeId::VARCHAR, 10, false,
                                   static_cast<catalog::col_oid_t>(++(*oid_counter)));
    warehouse_columns.emplace_back("W_STREET_1", type::TypeId::VARCHAR, 20, false,
                                   static_cast<catalog::col_oid_t>(++(*oid_counter)));
    warehouse_columns.emplace_back("W_STREET_2", type::TypeId::VARCHAR, 20, false,
                                   static_cast<catalog::col_oid_t>(++(*oid_counter)));
    warehouse_columns.emplace_back("W_CITY", type::TypeId::VARCHAR, 20, false,
                                   static_cast<catalog::col_oid_t>(++(*oid_counter)));
    warehouse_columns.emplace_back("W_STATE", type::TypeId::VARCHAR, 2, false,
                                   static_cast<catalog::col_oid_t>(++(*oid_counter)));
    warehouse_columns.emplace_back("W_ZIP", type::TypeId::VARCHAR, 9, false,
                                   static_cast<catalog::col_oid_t>(++(*oid_counter)));
    warehouse_columns.emplace_back("W_TAX", type::TypeId::DECIMAL, false,
                                   static_cast<catalog::col_oid_t>(++(*oid_counter)));
    warehouse_columns.emplace_back("W_YTD", type::TypeId::DECIMAL, false,
                                   static_cast<catalog::col_oid_t>(++(*oid_counter)));

    TERRIER_ASSERT(warehouse_columns.size() == num_warehouse_cols, "Wrong number of columns for Warehouse schema.");

    return catalog::Schema(warehouse_columns);
  }

  static catalog::Schema BuildStockSchema(uint64_t *const oid_counter) {
    std::vector<catalog::Schema::Column> stock_columns;
    stock_columns.reserve(num_stock_cols);

    stock_columns.emplace_back("S_I_ID", type::TypeId::INTEGER, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_W_ID", type::TypeId::INTEGER, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_QUANTITY", type::TypeId::SMALLINT, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_DIST_01", type::TypeId::VARCHAR, 24, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_DIST_02", type::TypeId::VARCHAR, 24, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_DIST_03", type::TypeId::VARCHAR, 24, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_DIST_04", type::TypeId::VARCHAR, 24, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_DIST_05", type::TypeId::VARCHAR, 24, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_DIST_06", type::TypeId::VARCHAR, 24, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_DIST_07", type::TypeId::VARCHAR, 24, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_DIST_08", type::TypeId::VARCHAR, 24, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_DIST_09", type::TypeId::VARCHAR, 24, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_DIST_10", type::TypeId::VARCHAR, 24, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_YTD", type::TypeId::INTEGER, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_ORDER_CNT", type::TypeId::SMALLINT, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_REMOTE_CNT", type::TypeId::SMALLINT, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    stock_columns.emplace_back("S_DATA", type::TypeId::VARCHAR, 50, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));

    TERRIER_ASSERT(stock_columns.size() == num_stock_cols, "Wrong number of columns for Stock schema.");

    return catalog::Schema(stock_columns);
  }

  static catalog::Schema BuildDistrictSchema(uint64_t *const oid_counter) {
    std::vector<catalog::Schema::Column> district_columns;
    district_columns.reserve(num_district_cols);

    district_columns.emplace_back("D_ID", type::TypeId::INTEGER, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    district_columns.emplace_back("D_W_ID", type::TypeId::INTEGER, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    district_columns.emplace_back("D_NAME", type::TypeId::VARCHAR, 10, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    district_columns.emplace_back("D_STREET_1", type::TypeId::VARCHAR, 20, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    district_columns.emplace_back("D_STREET_2", type::TypeId::VARCHAR, 20, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    district_columns.emplace_back("D_CITY", type::TypeId::VARCHAR, 20, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    district_columns.emplace_back("D_STATE", type::TypeId::VARCHAR, 2, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    district_columns.emplace_back("D_ZIP", type::TypeId::VARCHAR, 9, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    district_columns.emplace_back("D_TAX", type::TypeId::DECIMAL, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    district_columns.emplace_back("D_YTD", type::TypeId::DECIMAL, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    district_columns.emplace_back("D_NEXT_O_ID", type::TypeId::INTEGER, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));

    TERRIER_ASSERT(district_columns.size() == num_district_cols, "Wrong number of columns for District schema.");

    return catalog::Schema(district_columns);
  }

  static catalog::Schema BuildCustomerSchema(uint64_t *const oid_counter) {
    std::vector<catalog::Schema::Column> customer_columns;
    customer_columns.reserve(num_customer_cols);

    customer_columns.emplace_back("C_ID", type::TypeId::INTEGER, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_D_ID", type::TypeId::INTEGER, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_W_ID", type::TypeId::INTEGER, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_FIRST", type::TypeId::VARCHAR, 16, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_MIDDLE", type::TypeId::VARCHAR, 2, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_LAST", type::TypeId::VARCHAR, 16, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_STREET_1", type::TypeId::VARCHAR, 20, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_STREET_2", type::TypeId::VARCHAR, 20, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_CITY", type::TypeId::VARCHAR, 20, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_STATE", type::TypeId::VARCHAR, 2, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_ZIP", type::TypeId::VARCHAR, 9, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_PHONE", type::TypeId::VARCHAR, 16, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_SINCE", type::TypeId::TIMESTAMP, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_CREDIT", type::TypeId::VARCHAR, 2, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_CREDIT_LIM", type::TypeId::DECIMAL, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_DISCOUNT", type::TypeId::DECIMAL, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_BALANCE", type::TypeId::DECIMAL, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_YTD_PAYMENT", type::TypeId::DECIMAL, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_PAYMENT_CNT", type::TypeId::SMALLINT, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_DELIVERY_CNT", type::TypeId::SMALLINT, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));
    customer_columns.emplace_back("C_DATA", type::TypeId::VARCHAR, 500, false,
                                  static_cast<catalog::col_oid_t>(++(*oid_counter)));

    TERRIER_ASSERT(customer_columns.size() == num_customer_cols, "Wrong number of columns for Customer schema.");

    return catalog::Schema(customer_columns);
  }

  static catalog::Schema BuildHistorySchema(uint64_t *const oid_counter) {
    std::vector<catalog::Schema::Column> history_columns;
    history_columns.reserve(num_history_cols);

    history_columns.emplace_back("H_C_ID", type::TypeId::INTEGER, false,
                                 static_cast<catalog::col_oid_t>(++(*oid_counter)));
    history_columns.emplace_back("H_C_D_ID", type::TypeId::INTEGER, false,
                                 static_cast<catalog::col_oid_t>(++(*oid_counter)));
    history_columns.emplace_back("H_C_W_ID", type::TypeId::INTEGER, false,
                                 static_cast<catalog::col_oid_t>(++(*oid_counter)));
    history_columns.emplace_back("H_D_ID", type::TypeId::INTEGER, false,
                                 static_cast<catalog::col_oid_t>(++(*oid_counter)));
    history_columns.emplace_back("H_W_ID", type::TypeId::INTEGER, false,
                                 static_cast<catalog::col_oid_t>(++(*oid_counter)));
    history_columns.emplace_back("H_DATE", type::TypeId::TIMESTAMP, false,
                                 static_cast<catalog::col_oid_t>(++(*oid_counter)));
    history_columns.emplace_back("H_AMOUNT", type::TypeId::DECIMAL, false,
                                 static_cast<catalog::col_oid_t>(++(*oid_counter)));
    history_columns.emplace_back("H_DATA", type::TypeId::VARCHAR, 24, false,
                                 static_cast<catalog::col_oid_t>(++(*oid_counter)));

    TERRIER_ASSERT(history_columns.size() == num_history_cols, "Wrong number of columns for History schema.");

    return catalog::Schema(history_columns);
  }

  static catalog::Schema BuildNewOrderSchema(uint64_t *const oid_counter) {
    std::vector<catalog::Schema::Column> new_order_columns;
    new_order_columns.reserve(num_new_order_cols);

    new_order_columns.emplace_back("NO_O_ID", type::TypeId::INTEGER, false,
                                   static_cast<catalog::col_oid_t>(++(*oid_counter)));
    new_order_columns.emplace_back("NO_D_ID", type::TypeId::INTEGER, false,
                                   static_cast<catalog::col_oid_t>(++(*oid_counter)));
    new_order_columns.emplace_back("NO_W_ID", type::TypeId::INTEGER, false,
                                   static_cast<catalog::col_oid_t>(++(*oid_counter)));

    TERRIER_ASSERT(new_order_columns.size() == num_new_order_cols, "Wrong number of columns for New Order schema.");

    return catalog::Schema(new_order_columns);
  }

  static catalog::Schema BuildOrderSchema(uint64_t *const oid_counter) {
    std::vector<catalog::Schema::Column> order_columns;
    order_columns.reserve(num_order_cols);

    order_columns.emplace_back("O_ID", type::TypeId::INTEGER, false, static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_columns.emplace_back("O_D_ID", type::TypeId::INTEGER, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_columns.emplace_back("O_W_ID", type::TypeId::INTEGER, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_columns.emplace_back("O_C_ID", type::TypeId::INTEGER, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_columns.emplace_back("O_ENTRY_D", type::TypeId::TIMESTAMP, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_columns.emplace_back("O_CARRIER_ID", type::TypeId::INTEGER, true,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_columns.emplace_back("O_OL_CNT", type::TypeId::INTEGER, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_columns.emplace_back("O_ALL_LOCAL", type::TypeId::INTEGER, false,
                               static_cast<catalog::col_oid_t>(++(*oid_counter)));

    TERRIER_ASSERT(order_columns.size() == num_order_cols, "Wrong number of columns for Order schema.");

    return catalog::Schema(order_columns);
  }

  static catalog::Schema BuildOrderLineSchema(uint64_t *const oid_counter) {
    std::vector<catalog::Schema::Column> order_line_columns;
    order_line_columns.reserve(num_order_line_cols);

    order_line_columns.emplace_back("OL_O_ID", type::TypeId::INTEGER, false,
                                    static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_line_columns.emplace_back("OL_D_ID", type::TypeId::INTEGER, false,
                                    static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_line_columns.emplace_back("OL_W_ID", type::TypeId::INTEGER, false,
                                    static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_line_columns.emplace_back("OL_NUMBER", type::TypeId::INTEGER, false,
                                    static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_line_columns.emplace_back("OL_I_ID", type::TypeId::INTEGER, false,
                                    static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_line_columns.emplace_back("OL_SUPPLY_W_ID", type::TypeId::INTEGER, false,
                                    static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_line_columns.emplace_back("OL_DELIVERY_D", type::TypeId::TIMESTAMP, true,
                                    static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_line_columns.emplace_back("OL_QUANTITY", type::TypeId::INTEGER, false,
                                    static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_line_columns.emplace_back("OL_AMOUNT", type::TypeId::DECIMAL, false,
                                    static_cast<catalog::col_oid_t>(++(*oid_counter)));
    order_line_columns.emplace_back("OL_DIST_INFO", type::TypeId::VARCHAR, 24, false,
                                    static_cast<catalog::col_oid_t>(++(*oid_counter)));

    TERRIER_ASSERT(order_line_columns.size() == num_order_line_cols, "Wrong number of columns for Order Line schema.");

    return catalog::Schema(order_line_columns);
  }

 private:
  static constexpr uint8_t num_item_cols = 5;
  static constexpr uint8_t num_warehouse_cols = 9;
  static constexpr uint8_t num_stock_cols = 17;
  static constexpr uint8_t num_district_cols = 11;
  static constexpr uint8_t num_customer_cols = 21;
  static constexpr uint8_t num_history_cols = 8;
  static constexpr uint8_t num_new_order_cols = 3;
  static constexpr uint8_t num_order_cols = 8;
  static constexpr uint8_t num_order_line_cols = 10;
};

}