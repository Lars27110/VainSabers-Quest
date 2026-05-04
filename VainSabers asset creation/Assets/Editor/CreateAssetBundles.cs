using UnityEditor;

public class CreateAssetBundles
{
    [MenuItem ("Tools/Build AssetBundles")]
    static void BuildAllAssetBundles ()
    {
        BuildPipeline.BuildAssetBundles("../VainSabers/", BuildAssetBundleOptions.None, BuildTarget.StandaloneWindows);
    }
}