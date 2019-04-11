#pragma once

#include <string_view>
#include "storage/sql_table.h"
#include "storage/storage_defs.h"
#include "tpcc/database.h"
#include "tpcc/util.h"
#include "tpcc/workload.h"
#include "transaction/transaction_manager.h"
#include "util/transaction_benchmark_util.h"

namespace terrier::tpcc {

class NewOrder {
 private:
  struct StockSelectPROffsets {
    const uint8_t s_quantity_select_pr_offset;
    const uint8_t s_dist_xx_select_pr_offset;
    const uint8_t s_ytd_select_pr_offset;
    const uint8_t s_order_cnt_select_pr_offset;
    const uint8_t s_remote_cnt_select_pr_offset;
    const uint8_t s_data_select_pr_offset;
  };

  const storage::ProjectedRowInitializer warehouse_select_pr_initializer;

  const catalog::col_oid_t d_tax_oid;
  const catalog::col_oid_t d_next_o_id_oid;
  const storage::ProjectedRowInitializer district_select_pr_initializer;
  const storage::ProjectionMap district_select_pr_map;

  const uint8_t d_id_key_pr_offset;
  const uint8_t d_w_id_key_pr_offset;
  const uint8_t d_tax_select_pr_offset;
  const uint8_t d_next_o_id_select_pr_offset;
  const storage::ProjectedRowInitializer district_update_pr_initializer;

  const catalog::col_oid_t c_discount_oid;
  const catalog::col_oid_t c_last_oid;
  const catalog::col_oid_t c_credit_oid;
  const storage::ProjectedRowInitializer customer_select_pr_initializer;
  const storage::ProjectionMap customer_select_pr_map;
  const uint8_t c_discount_select_pr_offset;
  const uint8_t c_last_select_pr_offset;
  const uint8_t c_credit_select_pr_offset;
  const uint8_t c_id_key_pr_offset;
  const uint8_t c_d_id_key_pr_offset;
  const uint8_t c_w_id_key_pr_offset;

  const storage::ProjectedRowInitializer new_order_insert_pr_initializer;
  const storage::ProjectionMap new_order_insert_pr_map;
  const uint8_t no_o_id_insert_pr_offset;
  const uint8_t no_d_id_insert_pr_offset;
  const uint8_t no_w_id_insert_pr_offset;

  const uint8_t no_o_id_key_pr_offset;
  const uint8_t no_d_id_key_pr_offset;
  const uint8_t no_w_id_key_pr_offset;

  const storage::ProjectedRowInitializer order_insert_pr_initializer;
  const storage::ProjectionMap order_insert_pr_map;
  const uint8_t o_id_insert_pr_offset;
  const uint8_t o_d_id_insert_pr_offset;
  const uint8_t o_w_id_insert_pr_offset;
  const uint8_t o_c_id_insert_pr_offset;
  const uint8_t o_entry_d_insert_pr_offset;
  const uint8_t o_carrier_id_insert_pr_offset;
  const uint8_t o_ol_cnt_insert_pr_offset;
  const uint8_t o_all_local_insert_pr_offset;

  const uint8_t o_id_key_pr_offset;
  const uint8_t o_d_id_key_pr_offset;
  const uint8_t o_w_id_key_pr_offset;

  const catalog::col_oid_t i_price_oid;
  const catalog::col_oid_t i_name_oid;
  const catalog::col_oid_t i_data_oid;
  const storage::ProjectedRowInitializer item_select_pr_initializer;
  const storage::ProjectionMap item_select_pr_map;
  const uint8_t i_price_select_pr_offset;
  const uint8_t i_name_select_pr_offset;
  const uint8_t i_data_select_pr_offset;

  const catalog::col_oid_t s_quantity_oid;
  const catalog::col_oid_t s_ytd_oid;
  const catalog::col_oid_t s_order_cnt_oid;
  const catalog::col_oid_t s_remote_cnt_oid;
  const catalog::col_oid_t s_data_oid;
  const storage::ProjectedRowInitializer stock_update_pr_initializer;
  const storage::ProjectionMap stock_update_pr_map;
  const uint8_t s_quantity_update_pr_offset;
  const uint8_t s_ytd_update_pr_offset;
  const uint8_t s_order_cnt_update_pr_offset;
  const uint8_t s_remote_cnt_update_pr_offset;
  const uint8_t s_i_id_key_pr_offset;
  const uint8_t s_w_id_key_pr_offset;

  const storage::ProjectedRowInitializer order_line_insert_pr_initializer;
  const storage::ProjectionMap order_line_insert_pr_map;
  const uint8_t ol_o_id_insert_pr_offset;
  const uint8_t ol_d_id_insert_pr_offset;
  const uint8_t ol_w_id_insert_pr_offset;
  const uint8_t ol_number_insert_pr_offset;
  const uint8_t ol_i_id_insert_pr_offset;
  const uint8_t ol_supply_w_id_insert_pr_offset;
  const uint8_t ol_delivery_d_insert_pr_offset;
  const uint8_t ol_quantity_insert_pr_offset;
  const uint8_t ol_amount_insert_pr_offset;
  const uint8_t ol_dist_info_insert_pr_offset;
  const uint8_t ol_o_id_key_pr_offset;
  const uint8_t ol_d_id_key_pr_offset;
  const uint8_t ol_w_id_key_pr_offset;
  const uint8_t ol_number_key_pr_offset;

  std::vector<StockSelectPROffsets> stock_select_pr_offsets;
  std::vector<std::pair<storage::ProjectedRowInitializer, storage::ProjectionMap>> stock_select_initializers;

 public:
  explicit NewOrder(const Database *const db)

      // Warehouse metadata
      : warehouse_select_pr_initializer(
            db->warehouse_table_->InitializerForProjectedRow({db->warehouse_schema_.GetColumn(7).GetOid()}).first),

        // District metadata
        d_tax_oid(db->district_schema_.GetColumn(8).GetOid()),
        d_next_o_id_oid(db->district_schema_.GetColumn(10).GetOid()),
        district_select_pr_initializer(
            db->district_table_->InitializerForProjectedRow({d_tax_oid, d_next_o_id_oid}).first),
        district_select_pr_map(db->district_table_->InitializerForProjectedRow({d_tax_oid, d_next_o_id_oid}).second),
        d_id_key_pr_offset(db->district_index_->GetKeyOidToOffsetMap().at(db->district_key_schema_.at(1).GetOid())),
        d_w_id_key_pr_offset(db->district_index_->GetKeyOidToOffsetMap().at(db->district_key_schema_.at(0).GetOid())),
        d_tax_select_pr_offset(district_select_pr_map.at(d_tax_oid)),
        d_next_o_id_select_pr_offset(district_select_pr_map.at(d_next_o_id_oid)),
        district_update_pr_initializer(db->district_table_->InitializerForProjectedRow({d_next_o_id_oid}).first),

        // Customer metadata
        c_discount_oid(db->customer_schema_.GetColumn(15).GetOid()),
        c_last_oid(db->customer_schema_.GetColumn(5).GetOid()),
        c_credit_oid(db->customer_schema_.GetColumn(13).GetOid()),
        customer_select_pr_initializer(
            db->customer_table_->InitializerForProjectedRow({c_discount_oid, c_last_oid, c_credit_oid}).first),
        customer_select_pr_map(
            db->customer_table_->InitializerForProjectedRow({c_discount_oid, c_last_oid, c_credit_oid}).second),
        c_discount_select_pr_offset(customer_select_pr_map.at(c_discount_oid)),
        c_last_select_pr_offset(customer_select_pr_map.at(c_last_oid)),
        c_credit_select_pr_offset(customer_select_pr_map.at(c_credit_oid)),
        c_id_key_pr_offset(db->customer_index_->GetKeyOidToOffsetMap().at(db->customer_key_schema_.at(2).GetOid())),
        c_d_id_key_pr_offset(db->customer_index_->GetKeyOidToOffsetMap().at(db->customer_key_schema_.at(1).GetOid())),
        c_w_id_key_pr_offset(db->customer_index_->GetKeyOidToOffsetMap().at(db->customer_key_schema_.at(0).GetOid())),

        // New Order metadata
        new_order_insert_pr_initializer(
            db->new_order_table_->InitializerForProjectedRow(Util::AllColOidsForSchema(db->new_order_schema_)).first),
        new_order_insert_pr_map(
            db->new_order_table_->InitializerForProjectedRow(Util::AllColOidsForSchema(db->new_order_schema_)).second),
        no_o_id_insert_pr_offset(new_order_insert_pr_map.at(db->new_order_schema_.GetColumn(0).GetOid())),
        no_d_id_insert_pr_offset(new_order_insert_pr_map.at(db->new_order_schema_.GetColumn(1).GetOid())),
        no_w_id_insert_pr_offset(new_order_insert_pr_map.at(db->new_order_schema_.GetColumn(2).GetOid())),
        no_o_id_key_pr_offset(
            db->new_order_index_->GetKeyOidToOffsetMap().at(db->new_order_key_schema_.at(2).GetOid())),
        no_d_id_key_pr_offset(
            db->new_order_index_->GetKeyOidToOffsetMap().at(db->new_order_key_schema_.at(1).GetOid())),
        no_w_id_key_pr_offset(
            db->new_order_index_->GetKeyOidToOffsetMap().at(db->new_order_key_schema_.at(0).GetOid())),

        // Order metadata
        order_insert_pr_initializer(
            db->order_table_->InitializerForProjectedRow(Util::AllColOidsForSchema(db->order_schema_)).first),
        order_insert_pr_map(
            db->order_table_->InitializerForProjectedRow(Util::AllColOidsForSchema(db->order_schema_)).second),
        o_id_insert_pr_offset(order_insert_pr_map.at(db->order_schema_.GetColumn(0).GetOid())),
        o_d_id_insert_pr_offset(order_insert_pr_map.at(db->order_schema_.GetColumn(1).GetOid())),
        o_w_id_insert_pr_offset(order_insert_pr_map.at(db->order_schema_.GetColumn(2).GetOid())),
        o_c_id_insert_pr_offset(order_insert_pr_map.at(db->order_schema_.GetColumn(3).GetOid())),
        o_entry_d_insert_pr_offset(order_insert_pr_map.at(db->order_schema_.GetColumn(4).GetOid())),
        o_carrier_id_insert_pr_offset(order_insert_pr_map.at(db->order_schema_.GetColumn(5).GetOid())),
        o_ol_cnt_insert_pr_offset(order_insert_pr_map.at(db->order_schema_.GetColumn(6).GetOid())),
        o_all_local_insert_pr_offset(order_insert_pr_map.at(db->order_schema_.GetColumn(7).GetOid())),
        o_id_key_pr_offset(db->order_index_->GetKeyOidToOffsetMap().at(db->order_key_schema_.at(2).GetOid())),
        o_d_id_key_pr_offset(db->order_index_->GetKeyOidToOffsetMap().at(db->order_key_schema_.at(1).GetOid())),
        o_w_id_key_pr_offset(db->order_index_->GetKeyOidToOffsetMap().at(db->order_key_schema_.at(0).GetOid())),

        // Item metadata
        i_price_oid(db->item_schema_.GetColumn(3).GetOid()),
        i_name_oid(db->item_schema_.GetColumn(2).GetOid()),
        i_data_oid(db->item_schema_.GetColumn(4).GetOid()),
        item_select_pr_initializer(
            db->item_table_->InitializerForProjectedRow({i_price_oid, i_name_oid, i_data_oid}).first),
        item_select_pr_map(db->item_table_->InitializerForProjectedRow({i_price_oid, i_name_oid, i_data_oid}).second),
        i_price_select_pr_offset(item_select_pr_map.at(i_price_oid)),
        i_name_select_pr_offset(item_select_pr_map.at(i_name_oid)),
        i_data_select_pr_offset(item_select_pr_map.at(i_data_oid)),

        // Stock metadata
        s_quantity_oid(db->stock_schema_.GetColumn(2).GetOid()),
        s_ytd_oid(db->stock_schema_.GetColumn(13).GetOid()),
        s_order_cnt_oid(db->stock_schema_.GetColumn(14).GetOid()),
        s_remote_cnt_oid(db->stock_schema_.GetColumn(15).GetOid()),
        s_data_oid(db->stock_schema_.GetColumn(16).GetOid()),
        stock_update_pr_initializer(
            db->stock_table_->InitializerForProjectedRow({s_quantity_oid, s_ytd_oid, s_order_cnt_oid, s_remote_cnt_oid})
                .first),
        stock_update_pr_map(
            db->stock_table_->InitializerForProjectedRow({s_quantity_oid, s_ytd_oid, s_order_cnt_oid, s_remote_cnt_oid})
                .second),

        s_quantity_update_pr_offset(stock_update_pr_map.at(s_quantity_oid)),
        s_ytd_update_pr_offset(stock_update_pr_map.at(s_ytd_oid)),
        s_order_cnt_update_pr_offset(stock_update_pr_map.at(s_order_cnt_oid)),
        s_remote_cnt_update_pr_offset(stock_update_pr_map.at(s_remote_cnt_oid)),
        s_i_id_key_pr_offset(db->stock_index_->GetKeyOidToOffsetMap().at(db->stock_key_schema_.at(1).GetOid())),
        s_w_id_key_pr_offset(db->stock_index_->GetKeyOidToOffsetMap().at(db->stock_key_schema_.at(0).GetOid())),

        // Order Line metadata
        order_line_insert_pr_initializer(
            db->order_line_table_->InitializerForProjectedRow(Util::AllColOidsForSchema(db->order_line_schema_)).first),
        order_line_insert_pr_map(
            db->order_line_table_->InitializerForProjectedRow(Util::AllColOidsForSchema(db->order_line_schema_))
                .second),
        ol_o_id_insert_pr_offset(order_line_insert_pr_map.at(db->order_line_schema_.GetColumn(0).GetOid())),
        ol_d_id_insert_pr_offset(order_line_insert_pr_map.at(db->order_line_schema_.GetColumn(1).GetOid())),
        ol_w_id_insert_pr_offset(order_line_insert_pr_map.at(db->order_line_schema_.GetColumn(2).GetOid())),
        ol_number_insert_pr_offset(order_line_insert_pr_map.at(db->order_line_schema_.GetColumn(3).GetOid())),
        ol_i_id_insert_pr_offset(order_line_insert_pr_map.at(db->order_line_schema_.GetColumn(4).GetOid())),
        ol_supply_w_id_insert_pr_offset(order_line_insert_pr_map.at(db->order_line_schema_.GetColumn(5).GetOid())),
        ol_delivery_d_insert_pr_offset(order_line_insert_pr_map.at(db->order_line_schema_.GetColumn(6).GetOid())),
        ol_quantity_insert_pr_offset(order_line_insert_pr_map.at(db->order_line_schema_.GetColumn(7).GetOid())),
        ol_amount_insert_pr_offset(order_line_insert_pr_map.at(db->order_line_schema_.GetColumn(8).GetOid())),
        ol_dist_info_insert_pr_offset(order_line_insert_pr_map.at(db->order_line_schema_.GetColumn(9).GetOid())),
        ol_o_id_key_pr_offset(
            db->order_line_index_->GetKeyOidToOffsetMap().at(db->order_line_key_schema_.at(2).GetOid())),
        ol_d_id_key_pr_offset(
            db->order_line_index_->GetKeyOidToOffsetMap().at(db->order_line_key_schema_.at(1).GetOid())),
        ol_w_id_key_pr_offset(
            db->order_line_index_->GetKeyOidToOffsetMap().at(db->order_line_key_schema_.at(0).GetOid())),
        ol_number_key_pr_offset(
            db->order_line_index_->GetKeyOidToOffsetMap().at(db->order_line_key_schema_.at(3).GetOid()))

  {
    stock_select_initializers.reserve(10);
    for (uint8_t d_id = 0; d_id < 10; d_id++) {
      const auto s_dist_xx_oid = db->stock_schema_.GetColumn(3 + d_id).GetOid();
      stock_select_initializers.emplace_back((db->stock_table_->InitializerForProjectedRow(
          {s_quantity_oid, s_dist_xx_oid, s_ytd_oid, s_order_cnt_oid, s_remote_cnt_oid, s_data_oid})));
    }

    stock_select_pr_offsets.reserve(10);
    for (uint8_t d_id = 0; d_id < 10; d_id++) {
      const auto s_dist_xx_oid = db->stock_schema_.GetColumn(3 + d_id).GetOid();
      stock_select_pr_offsets.push_back(
          {static_cast<uint8_t>(stock_select_initializers[d_id].second.at(s_quantity_oid)),
           static_cast<uint8_t>(stock_select_initializers[d_id].second.at(s_dist_xx_oid)),
           static_cast<uint8_t>(stock_select_initializers[d_id].second.at(s_ytd_oid)),
           static_cast<uint8_t>(stock_select_initializers[d_id].second.at(s_order_cnt_oid)),
           static_cast<uint8_t>(stock_select_initializers[d_id].second.at(s_remote_cnt_oid)),
           static_cast<uint8_t>(stock_select_initializers[d_id].second.at(s_data_oid))});
    }
  }

  // 2.4.2
  template <class Random>
  bool Execute(transaction::TransactionManager *const txn_manager, Random *const generator, Database *const db,
               Worker *const worker, const TransactionArgs &args) const {
    double total_amount = 0;

    auto *const txn = txn_manager->BeginTransaction();

    // Look up W_ID in index
    const auto warehouse_key_pr_initializer = db->warehouse_index_->GetProjectedRowInitializer();
    auto *const warehouse_key = warehouse_key_pr_initializer.InitializeRow(worker->warehouse_key_buffer);

    *reinterpret_cast<int32_t *>(warehouse_key->AccessForceNotNull(0)) = args.w_id;

    std::vector<storage::TupleSlot> index_scan_results;
    db->warehouse_index_->ScanKey(*warehouse_key, &index_scan_results);
    TERRIER_ASSERT(index_scan_results.size() == 1, "Warehouse index lookup failed.");

    // Select W_TAX in table
    auto *const warehouse_select_tuple = warehouse_select_pr_initializer.InitializeRow(worker->warehouse_tuple_buffer);
    db->warehouse_table_->Select(txn, index_scan_results[0], warehouse_select_tuple);
    const auto w_tax = *reinterpret_cast<double *>(warehouse_select_tuple->AccessWithNullCheck(0));

    // Look up D_ID, W_ID in index
    const auto district_key_pr_initializer = db->district_index_->GetProjectedRowInitializer();
    auto *const district_key = district_key_pr_initializer.InitializeRow(worker->district_key_buffer);

    *reinterpret_cast<int32_t *>(district_key->AccessForceNotNull(d_id_key_pr_offset)) = args.d_id;
    *reinterpret_cast<int32_t *>(district_key->AccessForceNotNull(d_w_id_key_pr_offset)) = args.w_id;

    index_scan_results.clear();
    db->district_index_->ScanKey(*district_key, &index_scan_results);
    TERRIER_ASSERT(index_scan_results.size() == 1, "District index lookup failed.");

    // Select D_TAX, D_NEXT_O_ID in table
    auto *const district_select_tuple = district_select_pr_initializer.InitializeRow(worker->district_tuple_buffer);
    db->district_table_->Select(txn, index_scan_results[0], district_select_tuple);

    const auto d_tax = *reinterpret_cast<double *>(district_select_tuple->AccessWithNullCheck(d_tax_select_pr_offset));
    const auto d_next_o_id =
        *reinterpret_cast<int32_t *>(district_select_tuple->AccessWithNullCheck(d_next_o_id_select_pr_offset));

    // Increment D_NEXT_O_ID in table
    auto *const district_update_tuple = district_update_pr_initializer.InitializeRow(worker->district_tuple_buffer);
    *reinterpret_cast<int32_t *>(district_update_tuple->AccessForceNotNull(0)) = d_next_o_id + 1;

    bool result = db->district_table_->Update(txn, index_scan_results[0], *district_update_tuple);
    if (!result) {
      txn_manager->Abort(txn);
      return false;
    }

    // Look up C_ID, D_ID, W_ID in index
    const auto customer_key_pr_initializer = db->customer_index_->GetProjectedRowInitializer();
    auto *const customer_key = customer_key_pr_initializer.InitializeRow(worker->customer_key_buffer);

    *reinterpret_cast<int32_t *>(customer_key->AccessForceNotNull(c_id_key_pr_offset)) = args.c_id;
    *reinterpret_cast<int32_t *>(customer_key->AccessForceNotNull(c_d_id_key_pr_offset)) = args.d_id;
    *reinterpret_cast<int32_t *>(customer_key->AccessForceNotNull(c_w_id_key_pr_offset)) = args.w_id;

    index_scan_results.clear();
    db->customer_index_->ScanKey(*customer_key, &index_scan_results);
    TERRIER_ASSERT(index_scan_results.size() == 1, "Customer index lookup failed.");

    // Select C_DISCOUNT, C_LAST, and C_CREDIT in table
    auto *const customer_select_tuple = customer_select_pr_initializer.InitializeRow(worker->customer_tuple_buffer);
    db->customer_table_->Select(txn, index_scan_results[0], customer_select_tuple);
    const auto c_discount =
        *reinterpret_cast<double *>(customer_select_tuple->AccessWithNullCheck(c_discount_select_pr_offset));
    const auto UNUSED_ATTRIBUTE c_last =
        *reinterpret_cast<storage::VarlenEntry *>(customer_select_tuple->AccessWithNullCheck(c_last_select_pr_offset));
    const auto UNUSED_ATTRIBUTE c_credit = *reinterpret_cast<storage::VarlenEntry *>(
        customer_select_tuple->AccessWithNullCheck(c_credit_select_pr_offset));

    // Insert new row in New Order
    auto *const new_order_insert_tuple = new_order_insert_pr_initializer.InitializeRow(worker->new_order_key_buffer);

    *reinterpret_cast<int32_t *>(new_order_insert_tuple->AccessForceNotNull(no_o_id_insert_pr_offset)) = d_next_o_id;
    *reinterpret_cast<int32_t *>(new_order_insert_tuple->AccessForceNotNull(no_d_id_insert_pr_offset)) = args.d_id;
    *reinterpret_cast<int32_t *>(new_order_insert_tuple->AccessForceNotNull(no_w_id_insert_pr_offset)) = args.w_id;

    const auto new_order_slot = db->new_order_table_->Insert(txn, *new_order_insert_tuple);

    // insert in index
    const auto new_order_key_pr_initializer = db->new_order_index_->GetProjectedRowInitializer();
    auto *const new_order_key = new_order_key_pr_initializer.InitializeRow(worker->new_order_key_buffer);

    *reinterpret_cast<int32_t *>(new_order_key->AccessForceNotNull(no_o_id_key_pr_offset)) = d_next_o_id;
    *reinterpret_cast<int32_t *>(new_order_key->AccessForceNotNull(no_d_id_key_pr_offset)) = args.d_id;
    *reinterpret_cast<int32_t *>(new_order_key->AccessForceNotNull(no_w_id_key_pr_offset)) = args.w_id;

    bool UNUSED_ATTRIBUTE index_insert_result = db->new_order_index_->ConditionalInsert(
        *new_order_key, new_order_slot, [](const storage::TupleSlot &) { return false; });
    TERRIER_ASSERT(index_insert_result, "New Order index insertion failed.");

    // Insert new row in Order
    auto *const order_insert_tuple = order_insert_pr_initializer.InitializeRow(worker->order_tuple_buffer);

    *reinterpret_cast<int32_t *>(order_insert_tuple->AccessForceNotNull(o_id_insert_pr_offset)) = d_next_o_id;
    *reinterpret_cast<int32_t *>(order_insert_tuple->AccessForceNotNull(o_d_id_insert_pr_offset)) = args.d_id;
    *reinterpret_cast<int32_t *>(order_insert_tuple->AccessForceNotNull(o_w_id_insert_pr_offset)) = args.w_id;
    *reinterpret_cast<int32_t *>(order_insert_tuple->AccessForceNotNull(o_c_id_insert_pr_offset)) = args.c_id;
    *reinterpret_cast<uint64_t *>(order_insert_tuple->AccessForceNotNull(o_entry_d_insert_pr_offset)) = args.o_entry_d;
    order_insert_tuple->SetNull(o_carrier_id_insert_pr_offset);
    *reinterpret_cast<int32_t *>(order_insert_tuple->AccessForceNotNull(o_ol_cnt_insert_pr_offset)) = args.ol_cnt;
    *reinterpret_cast<int32_t *>(order_insert_tuple->AccessForceNotNull(o_all_local_insert_pr_offset)) =
        args.o_all_local;

    const auto order_slot = db->order_table_->Insert(txn, *order_insert_tuple);

    // insert in index
    const auto order_key_pr_initializer = db->order_index_->GetProjectedRowInitializer();
    auto *const order_key = order_key_pr_initializer.InitializeRow(worker->order_key_buffer);

    *reinterpret_cast<int32_t *>(order_key->AccessForceNotNull(o_id_key_pr_offset)) = d_next_o_id;
    *reinterpret_cast<int32_t *>(order_key->AccessForceNotNull(o_d_id_key_pr_offset)) = args.d_id;
    *reinterpret_cast<int32_t *>(order_key->AccessForceNotNull(o_w_id_key_pr_offset)) = args.w_id;

    index_insert_result =
        db->order_index_->ConditionalInsert(*order_key, order_slot, [](const storage::TupleSlot &) { return false; });
    TERRIER_ASSERT(index_insert_result, "Order index insertion failed.");

    const auto UNUSED_ATTRIBUTE ol_cnt = args.ol_cnt;

    // for each item in order
    for (const auto &item : args.items) {
      uint32_t ol_number = 1;

      // Look up I_ID in index
      const auto item_key_pr_initializer = db->item_index_->GetProjectedRowInitializer();
      auto *const item_key = item_key_pr_initializer.InitializeRow(worker->item_key_buffer);
      *reinterpret_cast<int32_t *>(item_key->AccessForceNotNull(0)) = item.ol_i_id;
      index_scan_results.clear();
      db->item_index_->ScanKey(*item_key, &index_scan_results);

      if (index_scan_results.empty()) {
        TERRIER_ASSERT(item.ol_i_id == 8491138, "It's the unused value.");
        txn_manager->Abort(txn);
        return false;
      }

      TERRIER_ASSERT(index_scan_results.size() == 1, "Item index lookup failed.");

      // Select I_PRICE, I_NAME, and I_DATE in table
      auto *const item_select_tuple = item_select_pr_initializer.InitializeRow(worker->item_tuple_buffer);
      db->item_table_->Select(txn, index_scan_results[0], item_select_tuple);
      const auto i_price =
          *reinterpret_cast<double *>(item_select_tuple->AccessWithNullCheck(i_price_select_pr_offset));
      const auto i_name UNUSED_ATTRIBUTE =
          *reinterpret_cast<storage::VarlenEntry *>(item_select_tuple->AccessWithNullCheck(i_name_select_pr_offset));
      const auto i_data =
          *reinterpret_cast<storage::VarlenEntry *>(item_select_tuple->AccessWithNullCheck(i_data_select_pr_offset));

      // Look up S_I_ID, S_W_ID in index
      const auto stock_key_pr_initializer = db->stock_index_->GetProjectedRowInitializer();
      auto *const stock_key = stock_key_pr_initializer.InitializeRow(worker->stock_key_buffer);

      *reinterpret_cast<int32_t *>(stock_key->AccessForceNotNull(s_i_id_key_pr_offset)) = item.ol_i_id;
      *reinterpret_cast<int32_t *>(stock_key->AccessForceNotNull(s_w_id_key_pr_offset)) = item.ol_supply_w_id;

      index_scan_results.clear();
      db->stock_index_->ScanKey(*stock_key, &index_scan_results);
      TERRIER_ASSERT(index_scan_results.size() == 1, "Stock index lookup failed.");

      // Select S_QUANTITY, S_DIST_xx (xx = args.d_id), S_YTD, S_ORDER_CNT, S_REMOTE_CNT, S_DATA in table
      auto *const stock_select_tuple =
          stock_select_initializers[args.d_id - 1].first.InitializeRow(worker->stock_tuple_buffer);
      db->stock_table_->Select(txn, index_scan_results[0], stock_select_tuple);
      const auto s_quantity = *reinterpret_cast<int16_t *>(
          stock_select_tuple->AccessWithNullCheck(stock_select_pr_offsets[args.d_id - 1].s_quantity_select_pr_offset));
      const auto s_dist_xx = *reinterpret_cast<storage::VarlenEntry *>(
          stock_select_tuple->AccessWithNullCheck(stock_select_pr_offsets[args.d_id - 1].s_dist_xx_select_pr_offset));
      const auto s_ytd = *reinterpret_cast<int32_t *>(
          stock_select_tuple->AccessWithNullCheck(stock_select_pr_offsets[args.d_id - 1].s_ytd_select_pr_offset));
      const auto s_order_cnt = *reinterpret_cast<int16_t *>(
          stock_select_tuple->AccessWithNullCheck(stock_select_pr_offsets[args.d_id - 1].s_order_cnt_select_pr_offset));
      const auto s_remote_cnt = *reinterpret_cast<int16_t *>(stock_select_tuple->AccessWithNullCheck(
          stock_select_pr_offsets[args.d_id - 1].s_remote_cnt_select_pr_offset));
      const auto s_data = *reinterpret_cast<storage::VarlenEntry *>(
          stock_select_tuple->AccessWithNullCheck(stock_select_pr_offsets[args.d_id - 1].s_data_select_pr_offset));

      // Update S_QUANTITY, S_YTD, S_ORDER_CNT, S_REMOTE_CNT
      auto *const stock_update_tuple = stock_update_pr_initializer.InitializeRow(worker->stock_tuple_buffer);
      *reinterpret_cast<int16_t *>(stock_update_tuple->AccessForceNotNull(s_quantity_update_pr_offset)) =
          (s_quantity >= item.ol_quantity + 10) ? s_quantity - item.ol_quantity : s_quantity - item.ol_quantity + 91;
      *reinterpret_cast<int32_t *>(stock_update_tuple->AccessForceNotNull(s_ytd_update_pr_offset)) =
          s_ytd + item.ol_quantity;
      *reinterpret_cast<int16_t *>(stock_update_tuple->AccessForceNotNull(s_order_cnt_update_pr_offset)) =
          s_order_cnt + 1;
      *reinterpret_cast<int16_t *>(stock_update_tuple->AccessForceNotNull(s_remote_cnt_update_pr_offset)) =
          item.remote ? s_remote_cnt + 1 : s_remote_cnt;

      result = db->stock_table_->Update(txn, index_scan_results[0], *stock_update_tuple);
      if (!result) {
        txn_manager->Abort(txn);
        return false;
      }

      const double ol_amount = item.ol_quantity * i_price;

      const std::string_view i_data_str(reinterpret_cast<const char *const>(i_data.Content()), i_data.Size());
      const std::string_view s_data_str(reinterpret_cast<const char *const>(s_data.Content()), s_data.Size());

      const std::string UNUSED_ATTRIBUTE brand_generic =
          i_data_str.find("ORIGINAL", 0) != std::string::npos && s_data_str.find("ORIGINAL", 0 != std::string::npos)
              ? "B"
              : "G";

      // Insert new row in Order Line
      auto *const order_line_insert_tuple =
          order_line_insert_pr_initializer.InitializeRow(worker->order_line_tuple_buffer);

      *reinterpret_cast<int32_t *>(order_line_insert_tuple->AccessForceNotNull(ol_o_id_insert_pr_offset)) = d_next_o_id;
      *reinterpret_cast<int32_t *>(order_line_insert_tuple->AccessForceNotNull(ol_d_id_insert_pr_offset)) = args.d_id;
      *reinterpret_cast<int32_t *>(order_line_insert_tuple->AccessForceNotNull(ol_w_id_insert_pr_offset)) = args.w_id;
      *reinterpret_cast<int32_t *>(order_line_insert_tuple->AccessForceNotNull(ol_number_insert_pr_offset)) = ol_number;
      *reinterpret_cast<int32_t *>(order_line_insert_tuple->AccessForceNotNull(ol_i_id_insert_pr_offset)) =
          item.ol_i_id;
      *reinterpret_cast<int32_t *>(order_line_insert_tuple->AccessForceNotNull(ol_supply_w_id_insert_pr_offset)) =
          item.ol_supply_w_id;
      order_line_insert_tuple->SetNull(ol_delivery_d_insert_pr_offset);
      *reinterpret_cast<int32_t *>(order_line_insert_tuple->AccessForceNotNull(ol_quantity_insert_pr_offset)) =
          item.ol_quantity;
      *reinterpret_cast<double *>(order_line_insert_tuple->AccessForceNotNull(ol_amount_insert_pr_offset)) =
          item.ol_quantity * i_price;

      if (s_dist_xx.Size() <= storage::VarlenEntry::InlineThreshold()) {
        *reinterpret_cast<storage::VarlenEntry *>(
            order_line_insert_tuple->AccessForceNotNull(ol_dist_info_insert_pr_offset)) = s_dist_xx;

      } else {
        auto *const varlen = common::AllocationUtil::AllocateAligned(s_dist_xx.Size());
        std::memcpy(varlen, s_dist_xx.Content(), s_dist_xx.Size());
        const auto varlen_entry = storage::VarlenEntry::Create(varlen, s_dist_xx.Size(), true);
        *reinterpret_cast<storage::VarlenEntry *>(
            order_line_insert_tuple->AccessForceNotNull(ol_dist_info_insert_pr_offset)) = varlen_entry;
      }

      const auto order_line_slot = db->order_line_table_->Insert(txn, *order_line_insert_tuple);

      // insert in index
      const auto order_line_key_pr_initializer = db->order_line_index_->GetProjectedRowInitializer();
      auto *const order_line_key = order_line_key_pr_initializer.InitializeRow(worker->order_line_key_buffer);

      *reinterpret_cast<int32_t *>(order_line_key->AccessForceNotNull(ol_w_id_key_pr_offset)) = args.w_id;
      *reinterpret_cast<int32_t *>(order_line_key->AccessForceNotNull(ol_d_id_key_pr_offset)) = args.d_id;
      *reinterpret_cast<int32_t *>(order_line_key->AccessForceNotNull(ol_o_id_key_pr_offset)) = d_next_o_id;
      *reinterpret_cast<int32_t *>(order_line_key->AccessForceNotNull(ol_number_key_pr_offset)) = ol_number;

      index_insert_result = db->order_line_index_->ConditionalInsert(*order_line_key, order_line_slot,
                                                                     [](const storage::TupleSlot &) { return false; });
      TERRIER_ASSERT(index_insert_result, "Order Line index insertion failed.");

      ol_number++;
      total_amount += ol_amount;
    }

    txn_manager->Commit(txn, TestCallbacks::EmptyCallback, nullptr);

    total_amount = total_amount * (1 - c_discount) * (1 + w_tax + d_tax);

    return true;
  }
};

}  // namespace terrier::tpcc