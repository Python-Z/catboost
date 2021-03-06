#pragma once

#include "enums.h"
#include "option.h"
#include "unimplemented_aware_option.h"

#include <util/generic/vector.h>
#include <util/system/types.h>

namespace NJson {
    class TJsonValue;
}

namespace NCatboostOptions {
    TString GetModelExtensionFromType(EModelType modelType);
    bool TryGetModelTypeFromExtension(TStringBuf modelExtension, EModelType& modelType);

    EModelType DefineModelFormat(TStringBuf modelPath);

    void AddExtension(TStringBuf extension, TString* modelFileName);

    class TOutputFilesOptions {
    public:
        explicit TOutputFilesOptions(ETaskType taskType);

        TOption<TString> ResultModelPath;
        TOption<bool> UseBestModel;
        TOption<int> BestModelMinTrees;

        const TString& GetTrainDir() const;

        TString CreateResultModelFullPath() const;

        TString CreateSnapshotFullPath() const;

        TString CreateOutputBordersFullPath() const;

        bool NeedSaveBorders() const;

        //local
        const TString& GetLearnErrorFilename() const;

        const TString& GetTestErrorFilename() const;

        const TString& GetTimeLeftLogFilename() const;

        const TString& GetMetaFileFilename() const;

        const TVector<EModelType>& GetModelFormats() const;

        bool ExportRequiresStaticCtrProvider() const;

        bool AddFileFormatExtension() const;

        const TString& GetJsonLogFilename() const;

        const TString& GetProfileLogFilename() const;

        const TString& GetResultModelFilename() const;

        const TString& GetSnapshotFilename() const;

        bool ShrinkModelToBestIteration() const;

        const TString& GetName() const;

        const TVector<EPredictionType>& GetPredictionTypes() const;

        const TVector<TString>& GetOutputColumns() const;

        bool AllowWriteFiles() const;

        EFinalCtrComputationMode GetFinalCtrComputationMode() const;

        bool SaveSnapshot() const;

        ui64 GetSnapshotSaveInterval() const;

        int GetVerbosePeriod() const;

        int GetMetricPeriod() const;

        TString CreateFstrRegularFullPath() const;

        TString CreateFstrIternalFullPath() const;

        TString CreateTrainingOptionsFullPath() const;

        TString CreateEvalFullPath() const;

        TString GetRocOutputPath() const;

        bool operator==(const TOutputFilesOptions& rhs) const;
        bool operator!=(const TOutputFilesOptions& rhs) const;

        void Save(NJson::TJsonValue* options) const;
        void Load(const NJson::TJsonValue& options);

        void Validate() const;

    private:
        TString GetFullPath(const TString& fileName) const;

    private:
        TOption<TString> TrainDir;
        TOption<TString> Name;
        TOption<TString> MetaFile;
        TOption<TString> JsonLogPath;
        TOption<TString> ProfileLogPath;
        TOption<TString> LearnErrorLogPath;
        TOption<TVector<EModelType>> ModelFormats;
        TOption<TString> TestErrorLogPath;
        TOption<TString> TimeLeftLog;
        TOption<TString> SnapshotPath;
        TOption<bool> SaveSnapshotFlag;
        TOption<bool> AllowWriteFilesFlag;
        TOption<EFinalCtrComputationMode> FinalCtrComputationMode;
        TOption<TString> EvalFileName;
        TOption<TString> FstrRegularFileName;
        TOption<TString> FstrInternalFileName;
        TOption<TString> TrainingOptionsFileName;

        TOption<ui64> SnapshotSaveIntervalSeconds;
        TGpuOnlyOption<TString> OutputBordersFileName;
        TOption<int> VerbosePeriod;
        TOption<int> MetricPeriod;

        TOption<TVector<EPredictionType>> PredictionTypes;
        TOption<TVector<TString>> OutputColumns;
        TOption<TString> RocOutputPath;
    };
}
