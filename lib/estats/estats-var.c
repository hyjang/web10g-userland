/*
 * Copyright (c) 2012 The Board of Trustees of the University of Illinois,
 *                    Carnegie Mellon University.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 *
 */
#include <estats/estats-int.h>

#define ESTATSVAR(_name_,_valtype_) (struct estats_var) { .name = #_name_, .valtype = ESTATS_##_valtype_ }

int max_index[MAX_TABLE] = { PERF_INDEX_MAX, PATH_INDEX_MAX, STACK_INDEX_MAX, APP_INDEX_MAX, TUNE_INDEX_MAX };

struct estats_var estats_var_array[TOTAL_INDEX_MAX] = {
        ESTATSVAR(SegsOut,UNSIGNED32),
        ESTATSVAR(DataSegsOut,UNSIGNED32),
        ESTATSVAR(DataOctetsOut,UNSIGNED32),
        ESTATSVAR(HCDataOctetsOut,UNSIGNED64),
        ESTATSVAR(SegsRetrans,UNSIGNED32),
        ESTATSVAR(OctetsRetrans,UNSIGNED32),
        ESTATSVAR(SegsIn,UNSIGNED32),
        ESTATSVAR(DataSegsIn,UNSIGNED32),
        ESTATSVAR(DataOctetsIn,UNSIGNED32),
        ESTATSVAR(HCDataOctetsIn,UNSIGNED64),
        ESTATSVAR(ElapsedSecs,UNSIGNED32),
        ESTATSVAR(ElapsedMicroSecs,UNSIGNED32),
        ESTATSVAR(StartTimeStamp,UNSIGNED8),
        ESTATSVAR(CurMSS,UNSIGNED32),
        ESTATSVAR(PipeSize,UNSIGNED32),
        ESTATSVAR(MaxPipeSize,UNSIGNED32),
        ESTATSVAR(SmoothedRTT,UNSIGNED32),
        ESTATSVAR(CurRTO,UNSIGNED32),
        ESTATSVAR(CongSignals,UNSIGNED32),
        ESTATSVAR(CurCwnd,UNSIGNED32),
        ESTATSVAR(CurSsthresh,UNSIGNED32),
        ESTATSVAR(Timeouts,UNSIGNED32),
        ESTATSVAR(CurRwinSent,UNSIGNED32),
        ESTATSVAR(MaxRwinSent,UNSIGNED32),
        ESTATSVAR(ZeroRwinSent,UNSIGNED32),
        ESTATSVAR(CurRwinRcvd,UNSIGNED32),
        ESTATSVAR(MaxRwinRcvd,UNSIGNED32),
        ESTATSVAR(ZeroRwinRcvd,UNSIGNED32),
        ESTATSVAR(SndLimTransRwin,UNSIGNED32),
        ESTATSVAR(SndLimTransCwnd,UNSIGNED32),
        ESTATSVAR(SndLimTransSnd,UNSIGNED32),
        ESTATSVAR(SndLimTimeRwin,UNSIGNED32),
        ESTATSVAR(SndLimTimeCwnd,UNSIGNED32),
        ESTATSVAR(SndLimTimeSnd,UNSIGNED32),

        ESTATSVAR(RetranThresh,UNSIGNED32),
        ESTATSVAR(NonRecovDAEpisodes,UNSIGNED32),
        ESTATSVAR(SumOctetsReordered,UNSIGNED32),
        ESTATSVAR(NonRecovDA,UNSIGNED32),
        ESTATSVAR(SampleRTT,UNSIGNED32),
        ESTATSVAR(RTTVar,UNSIGNED32),
        ESTATSVAR(MaxRTT,UNSIGNED32),
        ESTATSVAR(MinRTT,UNSIGNED32),
        ESTATSVAR(SumRTT,UNSIGNED32),
        ESTATSVAR(HCSumRTT,UNSIGNED64),
        ESTATSVAR(CountRTT,UNSIGNED32),
        ESTATSVAR(MaxRTO,UNSIGNED32),
        ESTATSVAR(MinRTO,UNSIGNED32),
        ESTATSVAR(IpTtl,UNSIGNED32),
        ESTATSVAR(IpTosIn,UNSIGNED8),
        ESTATSVAR(IpTosOut,UNSIGNED8),
        ESTATSVAR(PreCongSumCwnd,UNSIGNED32),
        ESTATSVAR(PreCongSumRTT,UNSIGNED32),
        ESTATSVAR(PostCongSumRTT,UNSIGNED32),
        ESTATSVAR(PostCongCountRTT,UNSIGNED32),
        ESTATSVAR(ECNsignals,UNSIGNED32),
        ESTATSVAR(DupAckEpisodes,UNSIGNED32),
        ESTATSVAR(RcvRTT,UNSIGNED32),
        ESTATSVAR(DupAcksOut,UNSIGNED32),
        ESTATSVAR(CERcvd,UNSIGNED32),
        ESTATSVAR(ECESent,UNSIGNED32),

	ESTATSVAR(ActiveOpen,SIGNED32),
	ESTATSVAR(MSSSent,UNSIGNED32),
	ESTATSVAR(MSSRcvd,UNSIGNED32),
	ESTATSVAR(WinScaleSent,SIGNED32),
	ESTATSVAR(WinScaleRcvd,SIGNED32),
	ESTATSVAR(TimeStamps,SIGNED32),
	ESTATSVAR(ECN,SIGNED32),
	ESTATSVAR(WillSendSACK,SIGNED32),
	ESTATSVAR(WillUseSACK,SIGNED32),
	ESTATSVAR(State,SIGNED32),
	ESTATSVAR(Nagle,SIGNED32),
	ESTATSVAR(MaxSsCwnd,UNSIGNED32),
	ESTATSVAR(MaxCaCwnd,UNSIGNED32),
	ESTATSVAR(MaxSsthresh,UNSIGNED32),
	ESTATSVAR(MinSsthresh,UNSIGNED32),
	ESTATSVAR(InRecovery,SIGNED32),
	ESTATSVAR(DupAcksIn,UNSIGNED32),
	ESTATSVAR(SpuriousFrDetected,UNSIGNED32),
	ESTATSVAR(SpuriousRtoDetected,UNSIGNED32),
	ESTATSVAR(SoftErrors,UNSIGNED32),
	ESTATSVAR(SoftErrorReason,SIGNED32),
	ESTATSVAR(SlowStart,UNSIGNED32),
	ESTATSVAR(CongAvoid,UNSIGNED32),
	ESTATSVAR(OtherReductions,UNSIGNED32),
	ESTATSVAR(CongOverCount,UNSIGNED32),
	ESTATSVAR(FastRetran,UNSIGNED32),
	ESTATSVAR(SubsequentTimeouts,UNSIGNED32),
	ESTATSVAR(CurTimeoutCount,UNSIGNED32),
	ESTATSVAR(AbruptTimeouts,UNSIGNED32),
	ESTATSVAR(SACKsRcvd,UNSIGNED32),
	ESTATSVAR(SACKBlocksRcvd,UNSIGNED32),
	ESTATSVAR(SendStall,UNSIGNED32),
	ESTATSVAR(DSACKDups,UNSIGNED32),
	ESTATSVAR(MaxMSS,UNSIGNED32),
	ESTATSVAR(MinMSS,UNSIGNED32),
	ESTATSVAR(SndInitial,UNSIGNED32),
	ESTATSVAR(RecInitial,UNSIGNED32),
	ESTATSVAR(CurRetxQueue,UNSIGNED32),
	ESTATSVAR(MaxRetxQueue,UNSIGNED32),
	ESTATSVAR(CurReasmQueue,UNSIGNED32),
	ESTATSVAR(MaxReasmQueue,UNSIGNED32),

        ESTATSVAR(SndUna,UNSIGNED32),
        ESTATSVAR(SndNxt,UNSIGNED32),
        ESTATSVAR(SndMax,UNSIGNED32),
        ESTATSVAR(ThruOctetsAcked,UNSIGNED32),
        ESTATSVAR(HCThruOctetsAcked,UNSIGNED64),
        ESTATSVAR(RcvNxt,UNSIGNED32),
        ESTATSVAR(ThruOctetsReceived,UNSIGNED32),
        ESTATSVAR(HCThruOctetsReceived,UNSIGNED64),
        ESTATSVAR(CurAppWQueue,UNSIGNED32),
        ESTATSVAR(MaxAppWQueue,UNSIGNED32),
        ESTATSVAR(CurAppRQueue,UNSIGNED32),
        ESTATSVAR(MaxAppRQueue,UNSIGNED32),

        ESTATSVAR(LimCwnd,UNSIGNED32),
        ESTATSVAR(LimSsthresh,UNSIGNED32),
        ESTATSVAR(LimRwin,UNSIGNED32),
        ESTATSVAR(LimMSS,UNSIGNED32),
};
