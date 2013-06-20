/*
 * Copyright (c) 2013 The Board of Trustees of the University of Illinois,
 *                    Carnegie Mellon University.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT License.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the MIT License for more details.
 *
 * You should have received a copy of the MIT License along with this library;
 * if not, see http://opensource.org/licenses/MIT.
 *
 */
#include <estats/estats-int.h>

#define ESTATSVAR(_name_,_valtype_,_type_) (struct estats_var) { .name = #_name_, .valtype = ESTATS_##_valtype_, .type = ESTATS_TYPE_##_type_ }

int max_index[MAX_TABLE] = { PERF_INDEX_MAX, PATH_INDEX_MAX, STACK_INDEX_MAX, APP_INDEX_MAX, TUNE_INDEX_MAX };

struct estats_var estats_var_array[TOTAL_INDEX_MAX] = {
        ESTATSVAR(SegsOut,UNSIGNED32,COUNTER32),
        ESTATSVAR(DataSegsOut,UNSIGNED32,COUNTER32),
        ESTATSVAR(DataOctetsOut,UNSIGNED32,COUNTER32),
        ESTATSVAR(HCDataOctetsOut,UNSIGNED64,COUNTER64),
        ESTATSVAR(SegsRetrans,UNSIGNED32,COUNTER32),
        ESTATSVAR(OctetsRetrans,UNSIGNED32,COUNTER32),
        ESTATSVAR(SegsIn,UNSIGNED32,COUNTER32),
        ESTATSVAR(DataSegsIn,UNSIGNED32,COUNTER32),
        ESTATSVAR(DataOctetsIn,UNSIGNED32,COUNTER32),
        ESTATSVAR(HCDataOctetsIn,UNSIGNED64,COUNTER64),
        ESTATSVAR(ElapsedSecs,UNSIGNED32,COUNTER32),
        ESTATSVAR(ElapsedMicroSecs,UNSIGNED32,COUNTER32),
        ESTATSVAR(StartTimeStamp,UNSIGNED8,TIME_TICKS),
        ESTATSVAR(CurMSS,UNSIGNED32,GAUGE32),
        ESTATSVAR(PipeSize,UNSIGNED32,GAUGE32),
        ESTATSVAR(MaxPipeSize,UNSIGNED32,GAUGE32),
        ESTATSVAR(SmoothedRTT,UNSIGNED32,GAUGE32),
        ESTATSVAR(CurRTO,UNSIGNED32,GAUGE32),
        ESTATSVAR(CongSignals,UNSIGNED32,COUNTER32),
        ESTATSVAR(CurCwnd,UNSIGNED32,GAUGE32),
        ESTATSVAR(CurSsthresh,UNSIGNED32,GAUGE32),
        ESTATSVAR(Timeouts,UNSIGNED32,COUNTER32),
        ESTATSVAR(CurRwinSent,UNSIGNED32,GAUGE32),
        ESTATSVAR(MaxRwinSent,UNSIGNED32,GAUGE32),
        ESTATSVAR(ZeroRwinSent,UNSIGNED32,GAUGE32),
        ESTATSVAR(CurRwinRcvd,UNSIGNED32,GAUGE32),
        ESTATSVAR(MaxRwinRcvd,UNSIGNED32,GAUGE32),
        ESTATSVAR(ZeroRwinRcvd,UNSIGNED32,GAUGE32),
        ESTATSVAR(SndLimTransRwin,UNSIGNED32,COUNTER32),
        ESTATSVAR(SndLimTransCwnd,UNSIGNED32,COUNTER32),
        ESTATSVAR(SndLimTransSnd,UNSIGNED32,COUNTER32),
        ESTATSVAR(SndLimTimeRwin,UNSIGNED32,COUNTER32),
        ESTATSVAR(SndLimTimeCwnd,UNSIGNED32,COUNTER32),
        ESTATSVAR(SndLimTimeSnd,UNSIGNED32,COUNTER32),

        ESTATSVAR(RetranThresh,UNSIGNED32,GAUGE32),
        ESTATSVAR(NonRecovDAEpisodes,UNSIGNED32,COUNTER32),
        ESTATSVAR(SumOctetsReordered,UNSIGNED32,COUNTER32),
        ESTATSVAR(NonRecovDA,UNSIGNED32,COUNTER32),
        ESTATSVAR(SampleRTT,UNSIGNED32,GAUGE32),
        ESTATSVAR(RTTVar,UNSIGNED32,GAUGE32),
        ESTATSVAR(MaxRTT,UNSIGNED32,GAUGE32),
        ESTATSVAR(MinRTT,UNSIGNED32,GAUGE32),
        ESTATSVAR(SumRTT,UNSIGNED32,COUNTER32),
        ESTATSVAR(HCSumRTT,UNSIGNED64,COUNTER64),
        ESTATSVAR(CountRTT,UNSIGNED32,COUNTER32),
        ESTATSVAR(MaxRTO,UNSIGNED32,GAUGE32),
        ESTATSVAR(MinRTO,UNSIGNED32,GAUGE32),
        ESTATSVAR(IpTtl,UNSIGNED32,UNSIGNED32),
        ESTATSVAR(IpTosIn,UNSIGNED8,OCTET),
        ESTATSVAR(IpTosOut,UNSIGNED8,OCTET),
        ESTATSVAR(PreCongSumCwnd,UNSIGNED32,COUNTER32),
        ESTATSVAR(PreCongSumRTT,UNSIGNED32,COUNTER32),
        ESTATSVAR(PostCongSumRTT,UNSIGNED32,COUNTER32),
        ESTATSVAR(PostCongCountRTT,UNSIGNED32,COUNTER32),
        ESTATSVAR(ECNsignals,UNSIGNED32,COUNTER32),
        ESTATSVAR(DupAckEpisodes,UNSIGNED32,COUNTER32),
        ESTATSVAR(RcvRTT,UNSIGNED32,GAUGE32),
        ESTATSVAR(DupAcksOut,UNSIGNED32,COUNTER32),
        ESTATSVAR(CERcvd,UNSIGNED32,COUNTER32),
        ESTATSVAR(ECESent,UNSIGNED32,COUNTER32),

	ESTATSVAR(ActiveOpen,SIGNED32,INTEGER),
	ESTATSVAR(MSSSent,UNSIGNED32,UNSIGNED32),
	ESTATSVAR(MSSRcvd,UNSIGNED32,UNSIGNED32),
	ESTATSVAR(WinScaleSent,SIGNED32,INTEGER32),
	ESTATSVAR(WinScaleRcvd,SIGNED32,INTEGER32),
	ESTATSVAR(TimeStamps,SIGNED32,INTEGER),
	ESTATSVAR(ECN,SIGNED32,INTEGER),
	ESTATSVAR(WillSendSACK,SIGNED32,INTEGER),
	ESTATSVAR(WillUseSACK,SIGNED32,INTEGER),
	ESTATSVAR(State,SIGNED32,INTEGER),
	ESTATSVAR(Nagle,SIGNED32,INTEGER),
	ESTATSVAR(MaxSsCwnd,UNSIGNED32,GAUGE32),
	ESTATSVAR(MaxCaCwnd,UNSIGNED32,GAUGE32),
	ESTATSVAR(MaxSsthresh,UNSIGNED32,GAUGE32),
	ESTATSVAR(MinSsthresh,UNSIGNED32,GAUGE32),
	ESTATSVAR(InRecovery,SIGNED32,INTEGER),
	ESTATSVAR(DupAcksIn,UNSIGNED32,COUNTER32),
	ESTATSVAR(SpuriousFrDetected,UNSIGNED32,COUNTER32),
	ESTATSVAR(SpuriousRtoDetected,UNSIGNED32,COUNTER32),
	ESTATSVAR(SoftErrors,UNSIGNED32,COUNTER32),
	ESTATSVAR(SoftErrorReason,SIGNED32,INTEGER),
	ESTATSVAR(SlowStart,UNSIGNED32,COUNTER32),
	ESTATSVAR(CongAvoid,UNSIGNED32,COUNTER32),
	ESTATSVAR(OtherReductions,UNSIGNED32,COUNTER32),
	ESTATSVAR(CongOverCount,UNSIGNED32,COUNTER32),
	ESTATSVAR(FastRetran,UNSIGNED32,COUNTER32),
	ESTATSVAR(SubsequentTimeouts,UNSIGNED32,COUNTER32),
	ESTATSVAR(CurTimeoutCount,UNSIGNED32,GAUGE32),
	ESTATSVAR(AbruptTimeouts,UNSIGNED32,COUNTER32),
	ESTATSVAR(SACKsRcvd,UNSIGNED32,COUNTER32),
	ESTATSVAR(SACKBlocksRcvd,UNSIGNED32,COUNTER32),
	ESTATSVAR(SendStall,UNSIGNED32,COUNTER32),
	ESTATSVAR(DSACKDups,UNSIGNED32,COUNTER32),
	ESTATSVAR(MaxMSS,UNSIGNED32,GAUGE32),
	ESTATSVAR(MinMSS,UNSIGNED32,GAUGE32),
	ESTATSVAR(SndInitial,UNSIGNED32,UNSIGNED32),
	ESTATSVAR(RecInitial,UNSIGNED32,UNSIGNED32),
	ESTATSVAR(CurRetxQueue,UNSIGNED32,GAUGE32),
	ESTATSVAR(MaxRetxQueue,UNSIGNED32,GAUGE32),
	ESTATSVAR(CurReasmQueue,UNSIGNED32,GAUGE32),
	ESTATSVAR(MaxReasmQueue,UNSIGNED32,GAUGE32),

        ESTATSVAR(SndUna,UNSIGNED32,COUNTER32),
        ESTATSVAR(SndNxt,UNSIGNED32,UNSIGNED32),
        ESTATSVAR(SndMax,UNSIGNED32,COUNTER32),
        ESTATSVAR(ThruOctetsAcked,UNSIGNED32,COUNTER32),
        ESTATSVAR(HCThruOctetsAcked,UNSIGNED64,COUNTER64),
        ESTATSVAR(RcvNxt,UNSIGNED32,COUNTER32),
        ESTATSVAR(ThruOctetsReceived,UNSIGNED32,COUNTER32),
        ESTATSVAR(HCThruOctetsReceived,UNSIGNED64,COUNTER64),
        ESTATSVAR(CurAppWQueue,UNSIGNED32,GAUGE32),
        ESTATSVAR(MaxAppWQueue,UNSIGNED32,GAUGE32),
        ESTATSVAR(CurAppRQueue,UNSIGNED32,GAUGE32),
        ESTATSVAR(MaxAppRQueue,UNSIGNED32,GAUGE32),

        ESTATSVAR(LimCwnd,UNSIGNED32,GAUGE32),
        ESTATSVAR(LimSsthresh,UNSIGNED32,GAUGE32),
        ESTATSVAR(LimRwin,UNSIGNED32,GAUGE32),
        ESTATSVAR(LimMSS,UNSIGNED32,GAUGE32),
};
