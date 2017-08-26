#ifndef ZHE_PACK_H
#define ZHE_PACK_H

#include "zeno-config-deriv.h"

struct out_conduit;
struct peerid;

void zhe_pack_vle16(uint16_t x);
zhe_paysize_t zhe_pack_vle16req(uint16_t x);
void zhe_pack_vle32(uint32_t x);
zhe_paysize_t zhe_pack_vle32req(uint32_t x);
void zhe_pack_vle64(uint64_t x);
zhe_paysize_t zhe_pack_vle64req(uint64_t x);
void zhe_pack_seq(seq_t x);
zhe_paysize_t zhe_pack_seqreq(seq_t x);
void zhe_pack_rid(zhe_rid_t x);
zhe_paysize_t zhe_pack_ridreq(zhe_rid_t x);
void zhe_pack_text(zhe_paysize_t n, const char *text);
void zhe_pack_mscout(zhe_address_t *dst);
void zhe_pack_mhello(zhe_address_t *dst);
void zhe_pack_mopen(zhe_address_t *dst, uint8_t seqnumlen, const struct peerid *ownid, zhe_timediff_t lease_dur);
void zhe_pack_maccept(zhe_address_t *dst, const struct peerid *ownid, const struct peerid *peerid, zhe_timediff_t lease_dur);
void zhe_pack_mclose(zhe_address_t *dst, uint8_t reason, const struct peerid *ownid);
void zhe_pack_reserve_mconduit(zhe_address_t *dst, struct out_conduit *oc, cid_t cid, zhe_paysize_t cnt);
void zhe_pack_msynch(zhe_address_t *dst, uint8_t sflag, cid_t cid, seq_t seqbase, seq_t cnt);
void zhe_pack_macknack(zhe_address_t *dst, cid_t cid, seq_t seq, uint32_t mask);
void zhe_pack_mping(zhe_address_t *dst, uint16_t hash);
void zhe_pack_mpong(zhe_address_t *dst, uint16_t hash);
void zhe_pack_mkeepalive(zhe_address_t *dst, const struct peerid *ownid);
int zhe_oc_pack_msdata(struct out_conduit *c, int relflag, zhe_rid_t rid, zhe_paysize_t payloadlen);
void zhe_oc_pack_msdata_payload(struct out_conduit *c, int relflag, zhe_paysize_t sz, const void *vdata);
void zhe_oc_pack_msdata_done(struct out_conduit *c, int relflag, zhe_time_t tnow);
int zhe_oc_pack_mdeclare(struct out_conduit *c, uint8_t ndecls, uint8_t decllen, zhe_msgsize_t *from);
void zhe_oc_pack_mdeclare_done(struct out_conduit *c, zhe_msgsize_t from, zhe_time_t tnow);
void zhe_pack_dresource(zhe_rid_t rid, const char *res);
void zhe_pack_dpub(zhe_rid_t rid);
void zhe_pack_dsub(zhe_rid_t rid);
void zhe_pack_dcommit(uint8_t commitid);
void zhe_pack_dresult(uint8_t commitid, uint8_t status, zhe_rid_t rid);

#endif
