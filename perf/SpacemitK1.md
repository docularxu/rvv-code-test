# Spacemit K1/M1 Supported Perf Events

| Event | Status | Event | Status | Event | Status | Event | Status |
| --- | --- | --- | --- | --- | --- | --- | --- |
| cycles | ✔️ | LLC-prefetches | ❌ | dtlb_load_miss | ✔️ | ecall_inst | ✔️ |
| branches | ✔️ | LLC-prefetch-misses | ❌ | dtlb_store_miss | ✔️ | failed_sc_inst | ✔️ |
| branch-misses | ✔️ | dTLB-loads | ❌ | itlb_load_miss | ✔️ | fence_inst | ✔️ |
| instructions | ✔️ | dTLB-load-misses | ✔️ | jtlb_miss | ✔️ | fp_div_inst | ✔️ |
| bus-cycles | ❌ | dTLB-stores | ❌ | l1d_access | ✔️ | fp_inst | ✔️ |
| ref-cycles | ❌ | dTLB-store-misses | ✔️ | l1d_amr_active | ✔️ | fp_load_inst | ✔️ |
| page-faults | ✔️ | dTLB-prefetches | ❌ | l1d_excl_evict | ✔️ | fp_store_inst | ✔️ |
| context-switches | ✔️ | dTLB-prefetch-misses | ❌ | l1d_load_access | ✔️ | load_inst | ✔️ |
| cpu-migrations | ✔️ | iTLB-loads | ❌ | l1d_load_miss | ✔️ | lr_inst | ✔️ |
| stalled-cycles-frontend | ✔️ | iTLB-load-misses | ✔️ | l1d_miss | ✔️ | mult_inst | ✔️ |
| stalled-cycles-backend | ✔️ | branch-loads | ❌ | l1d_prefetch_hit | ✔️ | sc_inst | ✔️ |
| task-clock | ✔️ | branch-load-misses | ❌ | l1d_prefetch_refill | ✔️ | store_inst | ✔️ |
| cache-misses | ❌ | node-loads | N/A | l1d_store_access | ✔️ | unaligned_load_inst | ✔️ |
| cache-references | ❌ | node-load-misses | N/A | l1d_store_miss | ✔️ | unaligned_store_inst | ✔️ |
| alignment-faults | ✔️ | node-stores | N/A | l1i_load_access | ✔️ | vector_div_inst | ✔️ |
| faults | ✔️ | node-store-misses | N/A | l1i_load_miss | ✔️ | vector_inst | ✔️ |
| L1-dcache-loads | ✔️ | node-prefetches | N/A | l1i_prefetch | ✔️ | vector_load_inst | ✔️ |
| L1-dcache-load-misses | ✔️ | node-prefetch-misses | N/A | l1i_prefetch_miss | ✔️ | vector_store_inst | ✔️ |
| L1-dcache-stores | ✔️ | br_inst | ✔️ | l2_ar_channel_request | ✔️ | Microarch系列除了以下指标为0，其余✔️ |  |
| L1-dcache-store-misses | ✔️ | br_mispred | ✔️ | l2_ar_channel_stall_cycle | ✔️ | bju_ibuf_stall | ❓ |
| L1-dcache-prefetches | ❌ | cond_br_inst | ✔️ | l2_aw_channel_stall_cycle | ✔️ | ecc_interrupt | ❓ |
| L1-dcache-prefetch-misses | ❌ | cond_br_mispred | ✔️ | l2_load_access | ✔️ | ib_fifo_stall | ❓ |
| L1-icache-loads | ✔️ | indirect_br_inst | ✔️ | l2_load_miss | ✔️ | ib_mispred_stall | ❓ |
| L1-icache-load-misses | ✔️ | indirect_br_mispred | ✔️ | l2_store_access | ✔️ | id_vsetvl_fof_stall | ❓ |
| L1-icache-prefetches | ✔️ | long_jump | ❓ | alu_inst | ✔️ | iu_mult_wb_stall | ❓ |
| L1-icache-prefetch-misses | ✔️ | taken_br_mispred | ✔️ | amo_inst | ✔️ | mult_inner_forward | ❓ |
| LLC-loads | ❌ | taken_cond_br_inst | ✔️ | atomic_inst | ✔️ | rtu_only_vfpu_not_no_op | ❓ |
| LLC-load-misses | ❌ | taken_cond_br_mispred | ✔️ | bus_fence_inst | ✔️ |  |  |
| LLC-stores | ❌ | uncond_br_inst | ✔️ | csr_inst | ✔️ |  |  |
| LLC-store-misses | ❌ | uncond_br_mispred | ✔️ | div_inst | ✔️ |  |  |

Reference: [SpacemiT Perf Usage Note](https://bianbu.spacemit.com/en/development/perf/)

