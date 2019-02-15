#include<cstdlib>
#include <iostream>
#include <string.h>
#include <vector>

//EPICS includes
//#include <recGbl.h>
//#include <alarm.h>
#include <iocsh.h>
#include <epicsExport.h>
#include <registryFunction.h>
#include <subRecord.h>
#include <genSubRecord.h>

//AsynPortDriver include
#include <asynPortDriver.h>

//SmarAct includes
#include "SmarActSI.h"
#include "SmarActSIConstants_PS.h"

#include "picoScaledrv.h"

//------------------------------------------ AsynPortDriver ------------------------------------------
PicoScaledrv::PicoScaledrv(const char *portName, const char *ip) 
	: asynPortDriver(portName, MAX_SIGNALS, NUM_PARAMS,
	asynInt32Mask | asynFloat64Mask | asynFloat64ArrayMask | asynOctetMask | asynDrvUserMask,// Interfaces that we implement
	asynInt32Mask | asynFloat64Mask | asynFloat64ArrayMask,	// Interfaces that do callbacks
	ASYN_MULTIDEVICE | ASYN_CANBLOCK, 1, /* ASYN_CANBLOCK=1, ASYN_MULTIDEVICE=1, autoConnect=1 */
	0, 0) /* Default priority and stack size */
{
	createParam(pos_ch0_waveformValueString, asynParamFloat64Array, &pos_ch0_waveformValue);
	createParam(vel_ch0_waveformValueString, asynParamFloat64Array, &vel_ch0_waveformValue);
	createParam(acc_ch0_waveformValueString, asynParamFloat64Array, &acc_ch0_waveformValue);
	createParam(swraw_ch0_analogInValueString, asynParamFloat64, &swraw_ch0_analogInValue);
	createParam(s2wraw_ch0_analogInValueString, asynParamFloat64, &s2wraw_ch0_analogInValue);
	createParam(swquality_ch0_analogInValueString, asynParamFloat64, &swquality_ch0_analogInValue);
	createParam(s2wquality_ch0_analogInValueString, asynParamFloat64, &s2wquality_ch0_analogInValue);
	createParam(cntrZero_ch0_analogInValueString, asynParamFloat64, &cntrZero_ch0_analogInValue);
	createParam(cntrOne_ch0_analogInValueString, asynParamFloat64, &cntrOne_ch0_analogInValue);
	createParam(envtemp_ch0_analogInValueString, asynParamFloat64, &envtemp_ch0_analogInValue);
	createParam(envHum_ch0_analogInValueString, asynParamFloat64, &envHum_ch0_analogInValue);
	createParam(envPress_ch0_analogInValueString, asynParamFloat64, &envPress_ch0_analogInValue);
	createParam(gpioAdc0_ch0_analogInValueString, asynParamFloat64, &gpioAdc0_ch0_analogInValue);
	createParam(gpioAdc1_ch0_analogInValueString, asynParamFloat64, &gpioAdc1_ch0_analogInValue);
	createParam(gpioAdc2_ch0_analogInValueString, asynParamFloat64, &gpioAdc2_ch0_analogInValue);
	createParam(calcSys0_ch0_analogInValueString, asynParamFloat64, &calcSys0_ch0_analogInValue);
	createParam(calcSys1_ch0_analogInValueString, asynParamFloat64, &calcSys1_ch0_analogInValue);
	createParam(calcSys2_ch0_analogInValueString, asynParamFloat64, &calcSys2_ch0_analogInValue);
	createParam(calcSys3_ch0_analogInValueString, asynParamFloat64, &calcSys3_ch0_analogInValue);
	createParam(calcSys4_ch0_analogInValueString, asynParamFloat64, &calcSys4_ch0_analogInValue);
	createParam(calcSys5_ch0_analogInValueString, asynParamFloat64, &calcSys5_ch0_analogInValue);
	createParam(calcSys6_ch0_analogInValueString, asynParamFloat64, &calcSys6_ch0_analogInValue);
	createParam(calcSys7_ch0_analogInValueString, asynParamFloat64, &calcSys7_ch0_analogInValue);
	createParam(pos_ch1_waveformValueString, asynParamFloat64Array, &pos_ch1_waveformValue);
	createParam(vel_ch1_waveformValueString, asynParamFloat64Array, &vel_ch1_waveformValue);
	createParam(acc_ch1_waveformValueString, asynParamFloat64Array, &acc_ch1_waveformValue);
	createParam(swraw_ch1_analogInValueString, asynParamFloat64, &swraw_ch1_analogInValue);
	createParam(s2wraw_ch1_analogInValueString, asynParamFloat64, &s2wraw_ch1_analogInValue);
	createParam(swquality_ch1_analogInValueString, asynParamFloat64, &swquality_ch1_analogInValue);
	createParam(s2wquality_ch1_analogInValueString, asynParamFloat64, &s2wquality_ch1_analogInValue);
	createParam(pos_ch2_waveformValueString, asynParamFloat64Array, &pos_ch2_waveformValue);
	createParam(vel_ch2_waveformValueString, asynParamFloat64Array, &vel_ch2_waveformValue);
	createParam(acc_ch2_waveformValueString, asynParamFloat64Array, &acc_ch2_waveformValue);
	createParam(swraw_ch2_analogInValueString, asynParamFloat64, &swraw_ch2_analogInValue);
	createParam(s2wraw_ch2_analogInValueString, asynParamFloat64, &s2wraw_ch2_analogInValue);
	createParam(swquality_ch2_analogInValueString, asynParamFloat64, &swquality_ch2_analogInValue);
	createParam(s2wquality_ch2_analogInValueString, asynParamFloat64, &s2wquality_ch2_analogInValue);
	createParam(ip_stringOutValueString, asynParamOctet, &ip_stringOutValue);
	createParam(fullaccess_binaryInValueString, asynParamInt32, &fullaccess_binaryInValue);
	createParam(connectionStatus_binaryInValueString, asynParamInt32, &connectionStatus_binaryInValue); 
	createParam(framerate_longOutValueString, asynParamInt32, &framerate_longOutValue);
	createParam(frameaggr_longOutValueString, asynParamInt32, &frameaggr_longOutValue);
	createParam(bufferaggr_mbboValueString, asynParamInt32, &bufferaggr_mbboValue);
	createParam(buffersnum_longOutValueString, asynParamInt32, &buffersnum_longOutValue);
	createParam(interleaving_binaryOutValueString, asynParamInt32, &interleaving_binaryOutValue);
	createParam(channelindx_mbboValueString, asynParamInt32, &channelindx_mbboValue);
	createParam(datasrcindx_mbboValueString, asynParamInt32, &datasrcindx_mbboValue);
	createParam(streammode_mbboValueString, asynParamInt32, &streammode_mbboValue);
	createParam(workingdistmin_longOutValueString, asynParamInt32, &workingdistmin_longOutValue);
	createParam(workingdistmax_longOutValueString, asynParamInt32, &workingdistmax_longOutValue);
	createParam(fiberlength_longOutValueString, asynParamInt32, &fiberlength_longOutValue);

	picoScale_open(ip);
}

// --- AsynPortDriver extended methods ---
asynStatus PicoScaledrv::writeInt32(asynUser *pasynUser, epicsInt32 value){
	    int function = pasynUser->reason;
	    int addr=0;
	    asynStatus status = asynSuccess;
	    const char* functionName = "writeInt32";

	    status = getAddress(pasynUser, &addr); if (status != asynSuccess) return(status);

	    /* Set the parameter in the parameter library. */
	    status = (asynStatus) setIntegerParam(addr, function, value);
		
		if(function==framerate_longOutValue){
			picoScale_setFramerate();
	    	}else if(function==channelindx_mbboValue){
			dataSource.address.channelIndex = (uint8_t) value;
		}else if(function==datasrcindx_mbboValue){
			dataSource.address.dataSourceIndex = (uint8_t) value;
		}else if(function==streammode_mbboValue){
			if(value==0){
				cout<<"EH NOIS NA FITA";
				picoScale_stream();
			}
	    	}


	    /* Do callbacks so higher layers see any changes */
	    status = (asynStatus) callParamCallbacks(addr, addr);

	    if (status) 
		epicsSnprintf(pasynUser->errorMessage, pasynUser->errorMessageSize, 
		          "%s:%s: status=%d, function=%d, value=%d", 
		          driverName, functionName, status, function, value);
	    else        
		asynPrint(pasynUser, ASYN_TRACEIO_DRIVER, 
		      "%s:%s: function=%d, value=%d\n", 
		      driverName, functionName, function, value);
	    return status;
}

asynStatus PicoScaledrv::writeFloat64(asynUser *pasynUser, epicsFloat64 value){
	    int function = pasynUser->reason;
	    asynStatus status = asynSuccess;
	    int addr=0;
	    static const char *functionName = "writeFloat64";

	    status = getAddress(pasynUser, &addr); if (status != asynSuccess) return(status);
	 
	    /* Set the parameter and readback in the parameter library. */
	    status = setDoubleParam(addr, function, value);

	    /* Do callbacks so higher layers see any changes */
	    callParamCallbacks(addr, addr);
	    if (status) 
		asynPrint(pasynUser, ASYN_TRACE_ERROR, 
		      "%s:%s: error, status=%d function=%d, value=%f\n", 
		      driverName, functionName, status, function, value);
	    else        
		asynPrint(pasynUser, ASYN_TRACEIO_DRIVER, 
		      "%s:%s: function=%d, value=%f\n", 
		      driverName, functionName, function, value);
	    return status;
}

asynStatus PicoScaledrv::writeOctet(asynUser *pasynUser, const char *value, size_t maxChars, size_t *nActual){
	    int addr=0;
	    int function = pasynUser->reason;
	    asynStatus status = asynSuccess;
	    static const char *functionName = "writeOctet";

	    status = getAddress(pasynUser, &addr); if (status != asynSuccess) return(status);

	    if(function==ip_stringOutValue){
		cout << "passei por aqui";
		//picoScale_open();
	    }

	    /* Set the parameter in the parameter library. */
	    status = (asynStatus)setStringParam(addr, function, (char *)value);

	     /* Do callbacks so higher layers see any changes */
	    status = (asynStatus)callParamCallbacks(addr, addr);

	    if (status) 
		epicsSnprintf(pasynUser->errorMessage, pasynUser->errorMessageSize, 
		          "%s:%s: status=%d, function=%d, value=%s", 
		          driverName, functionName, status, function, value);
	    else        
		asynPrint(pasynUser, ASYN_TRACEIO_DRIVER, 
		      "%s:%s: function=%d, value=%s\n", 
		      driverName, functionName, function, value);
	    //*nActual = nChars;
	    return status;
}

/*asynStatus PicoScaledrv::writeFloat64Array(asynUser *pasynUser, epicsFloat64 *value, size_t nElements){
	return asynStatus;
}*/

// ----------------------------

void PicoScaledrv::appendValue(void *pValue)
{
	int aux;
    VariantValue v;
/*
    switch (dataSource.dataType)
    {
        case SA_SI_INT8_DTYPE:
            v.i8value = *(const int8_t*)(pValue);
		cout<<v.i8value<<"\n";
            break;
        case SA_SI_UINT8_DTYPE:
            v.u8value = *(const uint8_t*)(pValue);
		cout<<v.u8value<<"\n";
            break;
        case SA_SI_INT16_DTYPE:
            v.i16value = *(const int16_t*)(pValue);
		cout<<v.i16value<<"\n";
            break;
        case SA_SI_UINT16_DTYPE:
            v.u16value = *(const uint16_t*)(pValue);
		cout<<v.u16value<<"\n";
            break;
        case SA_SI_INT32_DTYPE:
            v.i32value = *(const int32_t*)(pValue);
		cout<<v.i32value<<"\n";
            break;
        case SA_SI_UINT32_DTYPE:
            v.u32value = *(const uint32_t*)(pValue);
		cout<<v.u32value<<"\n";
            break;
        case SA_SI_INT48_DTYPE:
            v.i48value = *(const int64_t*)(pValue);
		cout<<"Como eu esperava: "<<v.i48value<<"\n";
            break;
        case SA_SI_UINT48_DTYPE:
            v.u48value = *(const uint64_t*)(pValue);
		cout<<v.u48value<<"\n";
            break;
        case SA_SI_INT64_DTYPE:
            v.i64value = *(const int64_t*)(pValue);
		cout<<"Como eu esperava: "<<v.i64value<<"\n";
            break;
        case SA_SI_UINT64_DTYPE:
            v.u64value = *(const uint64_t*)(pValue);
		cout<<"Como eu esperava: "<<v.u64value<<"\n";
            break;
        case SA_SI_FLOAT32_DTYPE:
            v.f32value = *(const float*)(pValue);
		cout<<v.f32value<<"\n";
            break;
        case SA_SI_FLOAT64_DTYPE:
            v.f64value = *(const double*)(pValue);
		cout<<v.f64value<<"\n";
            break;
        default:
            // shouldn't happen
            v.i32value = 0;
            break;
    }
*/
	switch(dataSource.address.channelIndex){
		case 0:
			switch(dataSource.address.dataSourceIndex){
				case 0:
					
					v.i48value = *(const int64_t*)(pValue);
					aux = (int) v.i48value;//<<32;
					//cout<<aux<<"\n";
					setIntegerParam(pos_ch0_waveformValue, aux); 
					//callParamCallbacks();
					//cout<<v.i48value<<"\n";
				break;
			}
		break;
		case 1:
		break;
		case 2:
		break;
	}
}

int32_t PicoScaledrv::getDataSize(int32_t dataType)
{
    switch (dataType)
    {
        case SA_SI_INT8_DTYPE:
        case SA_SI_UINT8_DTYPE:
            return 1;
            break;
        case SA_SI_INT16_DTYPE:
        case SA_SI_UINT16_DTYPE:
            return 2;
            break;
        case SA_SI_INT32_DTYPE:
        case SA_SI_UINT32_DTYPE:
        case SA_SI_FLOAT32_DTYPE:
            return 4;
            break;
        case SA_SI_INT48_DTYPE:
        case SA_SI_UINT48_DTYPE:
            // 48-bit values are extended to 64-bit values by default
        case SA_SI_INT64_DTYPE:
        case SA_SI_UINT64_DTYPE:
        case SA_SI_FLOAT64_DTYPE:
            return 8;
            break;
    }
    return 0;   // shouldn't happen
}

unsigned int PicoScaledrv::configureStream(SA_SI_Handle handle)
{
    // prepare stream data container for received data
    //streamData.dataSource.resize(streamConfig.enabledDataSources.size());
    // configure frame aggregation

	cout<<"CONFIG_STREAM"<<"\n";
	cout<<"Frame aggregation: " <<streamConfig.frameAggregation<<"\n";
	cout<<"Frame rate: "<<streamConfig.frameRate<<"\n";
	cout<<"Buffer Aggregation: "<<streamConfig.streamBufferAggregation<<"\n";
	cout<<"Interleaving: "<<streamConfig.interleavingEnabled<<"\n";
	cout<<"Num Buffers: "<<streamConfig.numberOfStreamBuffers;
	cout<<"\n";

    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_FRAME_AGGREGATION_PROP,0,0),streamConfig.frameAggregation);
    if (result != SA_SI_OK){
        return result;
    }
    // configure frame rate
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_FRAME_RATE_PROP,0,0),streamConfig.frameRate);
    if (result != SA_SI_OK){
	 return result;
    }
    // configure stream buffer aggregation
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMBUFFER_AGGREGATION_PROP,0,0),streamConfig.streamBufferAggregation);
    if (result != SA_SI_OK){
        return result;
    }
    // configure interleaving
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMBUFFERS_INTERLEAVED_PROP,0,0),streamConfig.interleavingEnabled);
    if (result != SA_SI_OK){
	   return result;
    }
    // configure number of stream buffers
    result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_NUMBER_OF_STREAMBUFFERS_PROP,0,0),streamConfig.numberOfStreamBuffers);
    if (result != SA_SI_OK){
        return result;
    }
    return SA_SI_OK;
}


void PicoScaledrv::processBuffer(const SA_SI_DataBuffer *buffer, vector<int32_t> datasrcs_dataSizes, int32_t frameSize)
{
    //FILE *fp;
    //fp = fopen("picoScale_positionMeasr.txt", "a");
    // Each buffer holds as many frames as we have defined by the stream
    // buffer aggregation.
    // The structure of the buffer depends on whether we use interleaving
    // or not and which data sources were enabled for streaming. In this
    // case we've enabled a position data source and a GPIO ADC.
    if (streamConfig.interleavingEnabled)
    {
        // The interleaved buffer structure is:
        //                    0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19
        //                  +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
        // buffer->data[0]: |            position           |  GPIO |            position           |  GPIO | ...
        //                  +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
        //                  |                frame 0                |                frame 1                |
        // The frame size is 10. In each frame the offset for the position is 0 and the offset
        // for the GPIO ADC is 8.
        // Since we use interleaving there is only one pointer
        // (buffer->data[0]) that points to the frames.
        for (unsigned int frame = 0; frame<buffer->info.numberOfFrames; frame++)
        {
            int32_t offset = 0;
            for (size_t dataSourceIterator=0; dataSourceIterator < buffer->info.numberOfSources; dataSourceIterator++)
            {
                void *dataSourceValue = &buffer->data[0][frame*frameSize + offset];
                offset += datasrcs_dataSizes[dataSourceIterator];
		appendValue(dataSourceValue);
            }
        }
    }
    else // non-interleaving
    {
        // The non-interleaved buffer structure is:
        //                    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
        //                  +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
        // buffer->data[0]: |            position           |            position           | ...
        //                  +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---
        //                  |            frame 0            |            frame 1            |
        //                    0   1   2   3
        //                  +---+---+---+---+---
        // buffer->data[1]: |  GPIO |  GPIO | ...
        //                  +---+---+---+---+---
        //                  |frame 0|frame 1|
        // There is a separate pointer for each enabled data source. In this case
        // buffer->data[0] has a frame size of 8 and buffer->data[1] has a frame
        // size of 2.
	//long int var = 0;	
        for (size_t dataSourceIterator = 0; dataSourceIterator < buffer->info.numberOfSources; dataSourceIterator++)
        {
            for (unsigned int frame = 0; frame < buffer->info.numberOfFrames; frame++)
	    {
		//fprintf(fp, "%li\n", var);
		//fputc(((int) buffer->data[dataSource][frame*streamConfig.enabledDataSources[dataSource].dataSize]), fp);
                void *dataSourceValue = &buffer->data[dataSourceIterator][frame*datasrcs_dataSizes[dataSourceIterator]];
            }
        }
	//fclose(fp);
    }
    // Note: The following code line is an example how it should *not* be
    // implemented. Printing to standard out is a relatively time consuming
    // operation and should be avoided at this place. At low data rates it
    // might work, but especially at high data rates the PicoScale generates
    // data faster than the host can process them, very likely leading to
    // a buffer overflow error!
    //cout << "Received " << buffer->info.numberOfFrames << " frames." << endl;
}

unsigned int PicoScaledrv::receiveStreamBuffer(SA_SI_Handle handle, unsigned int timeout, bool &lastFrame, vector<int32_t> datasrcs_dataSizes, int32_t frameSize)
{
    SA_SI_Event ev;
    unsigned int result = SA_SI_WaitForEvent(handle,&ev,timeout);
    if (result != SA_SI_OK)
        return result;
    if (ev.type == SA_SI_STREAMBUFFER_READY_EVENT)
    {
        // get buffer data
        //const SA_SI_DataBuffer *pBuffer;
        result = SA_SI_AcquireBuffer(handle,ev.bufferId,&pBuffer);
        if (result != SA_SI_OK)
            return result;
        processBuffer(pBuffer, datasrcs_dataSizes, frameSize);
        if (pBuffer->info.flags & SA_SI_STREAM_END_FLAG)
            lastFrame = true;
        result = SA_SI_ReleaseBuffer(handle,ev.bufferId);
        if (result != SA_SI_OK)
            return result;
    }
    else
    {
        //cout << "Received unexpected event type: " << ev.type << " (parameter: " << ev.devEventParameter << ")" << endl;
        return SA_SI_OTHER_ERROR;
    }
    return SA_SI_OK;
}

unsigned int PicoScaledrv::picoScale_open(const char *ip)
{	
	const char *locator_part1 = "network:";
	const char *locator_part2 = ":55555";
        char *locator	= (char*) calloc(strlen(locator_part1) + strlen(ip) + strlen(locator_part2) + 1, sizeof(char));
	strcpy(locator, locator_part1);
	strcat(locator, ip);
	strcat(locator, locator_part2);

	result = (SA_SI_Open(&handle, locator,""));
	
	if (result != SA_SI_OK)
    	{
		cout << "Could not connect to device. Check ERROR record.";
		return 1;
    	}
	
	return result;
}

unsigned int PicoScaledrv::picoScale_close()
{/*
	result = SA_SI_Close(handle);
	if (result != SA_SI_OK){
		//error
		return 1; //returning 1 so subroutine record stops processing
    	}
	picoScaledrv->setConnectionStatus_binaryOutValue(0);
	picoScaledrv->callParamCallbacks();*/
	return result;
}

unsigned int PicoScaledrv::picoScale_setFramerate()
{
	if(firstExe==false) getIntegerParam(framerate_longOutValue, &streamConfig.frameRate);
	else {
		streamConfig.frameRate=1;
		firstExe=false;
	}

	cout << "Frame rate: " << streamConfig.frameRate << "\n";
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_FRAME_RATE_PROP,0,0), streamConfig.frameRate);
	
	if (result != SA_SI_OK){
		//error
		cout<<"Erro: " << result;
		return 1; //returning 1 so subroutine record stops processing
    	}
	
	double preciseFrameRate;
	result = SA_SI_GetProperty_f64(handle, SA_SI_EPK(SA_SI_PRECISE_FRAME_RATE_PROP,0,0),&preciseFrameRate,0); //the real operation framerate set by picoScale
    	
	if (result != SA_SI_OK){
		//error
        	return 1; //returning 1 so subroutine record stops processing
    	}

	streamConfig.frameRate = (int32_t) preciseFrameRate;
	setIntegerParam(framerate_longOutValue, (int) preciseFrameRate);
	cout<<"Precise fram rate: " << streamConfig.frameRate;
	//frame aggregation based on framerate value accordingly to the Programming guide
	switch(streamConfig.frameRate){
		case 1:
		case 2:
		case 4:
		case 9:
		case 19:
		case 38:
			streamConfig.frameAggregation = (int32_t) 1;
		break;
		case 76:
			streamConfig.frameAggregation = (int32_t) 1;
		break;
		case 152:
			streamConfig.frameAggregation = (int32_t) 4;
		break;
		case 305:
			streamConfig.frameAggregation = (int32_t) 8;
		break;
		case 610:
			streamConfig.frameAggregation = (int32_t) 16;
		break;
		case 1220:
			streamConfig.frameAggregation = (int32_t) 32;
		break;
		case 2440:
			streamConfig.frameAggregation = (int32_t) 64;
		break;
		case 4880:
			streamConfig.frameAggregation = (int32_t) 128;
		break;
		case 9770:
			streamConfig.frameAggregation = (int32_t) 256;
		break;
		case 19530:
			streamConfig.frameAggregation = (int32_t) 512;
		break;
		case 625000:
		case 312500:
		case 156250:
		case 78130:
		case 39060:
			streamConfig.frameAggregation = (int32_t) 1024;
		break;
		case 10000000:
		case 5000000:
		case 2500000:
		case 1250000:
			streamConfig.frameAggregation = (int32_t) 1024;
		break;
	}
	int frameggr = (int) streamConfig.frameAggregation;
	setIntegerParam(frameaggr_longOutValue, frameggr);
	callParamCallbacks();
	cout << "Somos vencedores";
	return result;
}

unsigned int PicoScaledrv::picoScale_stream(){ //method for streaming a single datasource
	bool lastFrame = false;
	int channelIndex, datasrcIndex, interleavingMode, bufferAggr, buffersNum;

	getIntegerParam(channelindx_mbboValue, &channelIndex);
	getIntegerParam(datasrcindx_mbboValue, &datasrcIndex);

	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, channelIndex, datasrcIndex),&dataSource.dataType,0); 
	if (result != SA_SI_OK){
		//error
		return result;
	}

	dataSource.dataSize = getDataSize(dataSource.dataType);
	dataSource.address.channelIndex = channelIndex;
	dataSource.address.dataSourceIndex = datasrcIndex;
	
	getIntegerParam(interleaving_binaryOutValue, &interleavingMode);
	getIntegerParam(bufferaggr_mbboValue, &bufferAggr);
	getIntegerParam(buffersnum_longOutValue, &buffersNum);

	streamConfig.interleavingEnabled = (bool) interleavingMode;
    	streamConfig.streamBufferAggregation = bufferAggr;
    	streamConfig.numberOfStreamBuffers = buffersNum;

	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,0,0),SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}
	result = configureStream(handle);
    	if (result != SA_SI_OK){
		//error
		return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_MODE_PROP,0,0),SA_SI_DIRECT_STREAMING);
	if (result != SA_SI_OK){
		//error
        	return result;
	}
    	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}	
	
	cout <<"AQUI MEU BEM";
	stream_datasrcs_sizes = {dataSource.dataSize};

	while (!lastFrame)
    	{
		result = receiveStreamBuffer(handle, 2000, lastFrame, stream_datasrcs_sizes, dataSource.dataSize);
		if (result != SA_SI_OK)
			//error    
			return result;
    	}
	
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_DISABLED);
    	if (result != SA_SI_OK) return result; //error
	return SA_SI_OK;	
}

unsigned int PicoScaledrv::picoScale_streamPVA_allChannels(){//method for streaming position/velocity/acceleration measurements from all channels
	/*bool lastFrame = false;
	int *interleavingMode, *bufferAggr, *buffersNum;

	picoScaledrv->getInterleaving_binaryOutValue(interleavingMode);
	picoScaledrv->getBufferaggr_mbboValue(bufferAggr);
	picoScaledrv->getBuffersnum_longOutValue(buffersNum);

	streamConfig.interleavingEnabled = (bool) *interleavingMode;
    	streamConfig.streamBufferAggregation = *bufferAggr;
    	streamConfig.numberOfStreamBuffers = *buffersNum;

	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,0,0),SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,0,1),SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,0,2),SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,1,0),SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,1,1),SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,1,2),SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,2,0),SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,2,1),SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,2,2),SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}

	result = configureStream(handle);
    	if (result != SA_SI_OK){
		//error
		return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_MODE_PROP,0,0),SA_SI_DIRECT_STREAMING);
	if (result != SA_SI_OK){
		//error
        	return result;
	}
    	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}	
	
	while (!lastFrame)
    	{
		result = receiveStreamBuffer(handle, 2000, lastFrame, streamPVA_allchannels_datasrcs_sizes, streamPVA_allchannels_frame_size);
		if (result != SA_SI_OK) return result;//error
    	}

	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_DISABLED);
    	if (result != SA_SI_OK) return result; //error
*/
	return SA_SI_OK;	
}

unsigned int PicoScaledrv::picoScale_streamPosition_allChannels(){//method for streaming position measurements from all (3) channels	
	/*bool lastFrame = false;
	int *interleavingMode, *bufferAggr, *buffersNum;
	
	picoScaledrv->getInterleaving_binaryOutValue(interleavingMode);
	picoScaledrv->getBufferaggr_mbboValue(bufferAggr);
	picoScaledrv->getBuffersnum_longOutValue(buffersNum);

	streamConfig.interleavingEnabled = (bool) *interleavingMode;
    	streamConfig.streamBufferAggregation = *bufferAggr;
    	streamConfig.numberOfStreamBuffers = *buffersNum;

	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,0,0),SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,1,0),SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ENABLED_PROP,2,0),SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}

	result = configureStream(handle);
    	if (result != SA_SI_OK){
		//error
		return result;
	}
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_MODE_PROP,0,0),SA_SI_DIRECT_STREAMING);
	if (result != SA_SI_OK){
		//error
        	return result;
	}
    	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_ENABLED);
	if (result != SA_SI_OK){
		//error
        	return result;
	}	
	
	while (!lastFrame)
    	{
		result = receiveStreamBuffer(handle, 2000, lastFrame, streamPosition_allchannels_datasrcs_sizes, streamPosition_allchannels_frame_size);
		if (result != SA_SI_OK) return result; //error
    	}
	
	result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_SI_STREAMING_ACTIVE_PROP, 0, 0), SA_SI_DISABLED);
    	if (result != SA_SI_OK) return result;//error
*/
	return SA_SI_OK;	
}

unsigned int PicoScaledrv::picoScale_poll(){
	return SA_SI_OK;
}

unsigned int PicoScaledrv::picoScale_adjust(){
// activate manual adjustment phase
	/*result = SA_SI_SetProperty_i32(handle, SA_SI_EPK(SA_PS_AF_ADJUSTMENT_STATE_PROP,0,0),SA_PS_ADJUSTMENT_STATE_MANUAL_ADJUST);
    	if (result != SA_SI_OK)	return result; //error
    
	return SA_SI_OK;*/
}

//--------------------------------------------------------------------------------------------------------

//------------------------------------------ IOC Shell Functions ------------------------------------------
//--- Create driver function
extern "C" int PicoScaleCreateDriver(const char *portName, const char *ip){
	PicoScaledrv *picoScaledrv = new PicoScaledrv(portName, ip);
	return(asynSuccess);
}

static const iocshArg portNameArg = { "Port name", iocshArgString};
static const iocshArg ipArg = { "IP", iocshArgString};
static const iocshArg * const createDriverArgs[] = {&portNameArg, &ipArg};
static const iocshFuncDef createDriverFuncDef = {"PicoScaleCreateDriver", 2, createDriverArgs};

static void createDriverCallFunc(const iocshArgBuf *args){
	PicoScaleCreateDriver(args[0].sval, args[1].sval);
}

void drvPicoScaleRegister(void){
	iocshRegister(&createDriverFuncDef,createDriverCallFunc);
}

extern "C" {
	epicsExportRegistrar(drvPicoScaleRegister);
}
//---

//--- Initializing routines
//extern "C" int 
unsigned int PicoScaledrv::PicoScaleInitializingRoutinesRun(){ //Should be called from st.cmd script right after calling 'PicoScaleCreateDriver(portName)'. This procedure asks PicoScale for each datasource type; 									in this way, it's possible to determine the frame's sizes of streams and, also, distinguish each datasource in a stream in interleaved mode
	
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 0, 0),&dataSourceP0,0); 
	if (result != SA_SI_OK){
		//error		
		return result;
	}

	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 0, 1),&dataSourceV0,0); 
	if (result != SA_SI_OK){
		//error
		return result;
	}
	
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 0, 2),&dataSourceA0,0); 
	if (result != SA_SI_OK){
		//error
		return result;
	}
	
	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 1, 0),&dataSourceP1,0); 
	if (result != SA_SI_OK){
		//error
		return result;
	}

	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 1, 1),&dataSourceV1,0); 
	if (result != SA_SI_OK){
		//error
		return result;
	}

	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 1, 2),&dataSourceA1,0); 
	if (result != SA_SI_OK){
		//error
		return result;
	}

	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 2, 0),&dataSourceP2,0); 
	if (result != SA_SI_OK){
		//error
		return result;
	}

	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 2, 1),&dataSourceV2,0); 
	if (result != SA_SI_OK){
		//error
		return result;
	}

	result = SA_SI_GetProperty_i32(handle, SA_SI_EPK(SA_SI_DATA_TYPE_PROP, 2, 2),&dataSourceA2,0); 
	if (result != SA_SI_OK){
		//error
		return result;
	}

	streamPVA_allchannels_datasrcs_sizes = {getDataSize(dataSourceP0), getDataSize(dataSourceV0), getDataSize(dataSourceA0),
						getDataSize(dataSourceP1), getDataSize(dataSourceV1), getDataSize(dataSourceA1),
						getDataSize(dataSourceP2), getDataSize(dataSourceV2), getDataSize(dataSourceA2)};

	streamPosition_allchannels_datasrcs_sizes = {getDataSize(dataSourceP0), getDataSize(dataSourceP1), getDataSize(dataSourceP2)};

	for(unsigned int i=0; i<streamPVA_allchannels_datasrcs_sizes.size(); i++){
		streamPVA_allchannels_frame_size += streamPVA_allchannels_datasrcs_sizes[i];	
	}
	
	for(unsigned int i=0; i<streamPosition_allchannels_datasrcs_sizes.size(); i++){
		streamPosition_allchannels_frame_size += streamPosition_allchannels_datasrcs_sizes[i];	
	}

	return(asynSuccess);
}
/*
static const iocshFuncDef initializingRoutinesFuncDef = {"PicoScaleInitializingRoutinesRun"};//, 1, configArgs};

static void initializingRoutinesCallFunc(const iocshArgBuf *args){
	PicoScaleInitializingRoutinesRun();
}

void initPicoScaleRegister(void){
	iocshRegister(&initializingRoutinesFuncDef,initializingRoutinesCallFunc);
}

extern "C" {
	epicsExportRegistrar(initPicoScaleRegister);
}*/
//---
//----------------------------------------------------------------------------------------------------------

